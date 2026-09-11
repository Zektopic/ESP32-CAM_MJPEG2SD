#!/usr/bin/env python3
import urllib.request
import urllib.error
import time
import json
import os
from concurrent.futures import ThreadPoolExecutor

BASE_URL = "http://192.168.1.78"
SCREENSHOTS_DIR = "/home/manupa/ESP32-CAM_MJPEG2SD/review_artifacts/screenshots"
OUTPUT_JSON = "/home/manupa/ESP32-CAM_MJPEG2SD/review_artifacts/benchmarks/perf_metrics.json"

os.makedirs(SCREENSHOTS_DIR, exist_ok=True)
os.makedirs(os.path.dirname(OUTPUT_JSON), exist_ok=True)

def get_status():
    try:
        req = urllib.request.Request(f"{BASE_URL}/status")
        with urllib.request.urlopen(req, timeout=5) as resp:
            return json.loads(resp.read().decode('utf-8'))
    except Exception as e:
        print(f"Error fetching status: {e}")
        return {}

def set_control(param, val):
    try:
        req = urllib.request.Request(f"{BASE_URL}/control?{param}={val}")
        with urllib.request.urlopen(req, timeout=5) as resp:
            return resp.read()
    except Exception as e:
        print(f"Error setting control {param}={val}: {e}")
        return None

def reset_stream_task():
    try:
        req = urllib.request.Request(f"{BASE_URL}/sustain?stream=0", method='HEAD')
        with urllib.request.urlopen(req, timeout=3) as resp:
            pass
    except Exception as e:
        pass
    time.sleep(0.3)

def benchmark_still(name, count=3):
    latencies = []
    sizes = []
    saved = False
    for i in range(count):
        t0 = time.time()
        ts = int(time.time() * 1000)
        req = urllib.request.Request(f"{BASE_URL}/control?still={ts}")
        try:
            with urllib.request.urlopen(req, timeout=8) as resp:
                data = resp.read()
                elapsed = time.time() - t0
                latencies.append(elapsed)
                sizes.append(len(data))
                if not saved and len(data) > 0:
                    filepath = os.path.join(SCREENSHOTS_DIR, f"capture_{name}.jpg")
                    with open(filepath, "wb") as f:
                        f.write(data)
                    saved = True
        except Exception as e:
            print(f"  Capture error on sample {i}: {e}")
        time.sleep(0.5)

    if not latencies:
        return {"avg_latency_s": 0, "min_latency_s": 0, "max_latency_s": 0, "avg_size_bytes": 0}
    return {
        "avg_latency_s": round(sum(latencies) / len(latencies), 3),
        "min_latency_s": round(min(latencies), 3),
        "max_latency_s": round(max(latencies), 3),
        "avg_size_bytes": int(sum(sizes) / len(sizes))
    }

def benchmark_stream(name, duration=5.0):
    reset_stream_task()
    time.sleep(0.2)
    req = urllib.request.Request(f"{BASE_URL}/sustain?stream=0")
    frame_count = 0
    total_bytes = 0
    t0 = time.time()
    try:
        with urllib.request.urlopen(req, timeout=6) as resp:
            buf = b""
            while time.time() - t0 < duration:
                chunk = resp.read(4096)
                if not chunk:
                    break
                buf += chunk
                while b"\xff\xd9" in buf:
                    idx = buf.find(b"\xff\xd9")
                    frame = buf[:idx+2]
                    buf = buf[idx+2:]
                    frame_count += 1
                    total_bytes += len(frame)
    except Exception as e:
        print(f"  Stream read note ({name}): {e}")
    finally:
        reset_stream_task()

    elapsed = time.time() - t0
    fps = round(frame_count / max(elapsed, 0.001), 2)
    kbps = round((total_bytes / 1024) / max(elapsed, 0.001), 1)
    avg_frame_size = round(total_bytes / max(1, frame_count) / 1024, 2)
    return {
        "duration_s": round(elapsed, 2),
        "frames_received": frame_count,
        "fps": fps,
        "throughput_kb_s": kbps,
        "avg_frame_kb": avg_frame_size
    }

def stress_test_webserver(n_requests=10, workers=5):
    urls = [f"{BASE_URL}/status" for _ in range(n_requests)]
    def fetch(u):
        t0 = time.time()
        try:
            req = urllib.request.Request(u)
            with urllib.request.urlopen(req, timeout=4) as resp:
                resp.read()
                return (True, time.time() - t0)
        except Exception:
            return (False, time.time() - t0)

    t_start = time.time()
    with ThreadPoolExecutor(max_workers=workers) as pool:
        results = list(pool.map(fetch, urls))
    total_time = time.time() - t_start
    successes = sum(1 for r in results if r[0])
    lats = [r[1] for r in results if r[0]]
    return {
        "total_requests": n_requests,
        "success_rate_pct": round((successes / n_requests) * 100, 1),
        "total_duration_s": round(total_time, 3),
        "avg_req_latency_s": round(sum(lats) / len(lats), 3) if lats else 0
    }

def main():
    print("=== ESP32-CAM PERFORMANCE & HARDWARE BENCHMARK ===")
    initial_status = get_status()
    print(f"Target Device: {BASE_URL}")
    print(f"Firmware: {initial_status.get('fw_version')} | Camera: {initial_status.get('camModel')}")
    print(f"Heap Free: {initial_status.get('free_heap')} | PSRAM Free: {initial_status.get('free_psram')}")
    print(f"Storage: {initial_status.get('card')} ({initial_status.get('used_bytes')}/{initial_status.get('total_bytes')})")
    print(f"WiFi RSSI: {initial_status.get('wifi_rssi')} | Uptime: {initial_status.get('up_time')}")
    print("--------------------------------------------------")

    # Disable motion detection for raw throughput benchmark
    print("Setting motion detection to OFF for baseline camera throughput...")
    set_control("enableMotion", "0")
    time.sleep(1)

    resolutions = [
        {"name": "QVGA_320x240", "id": "5"},
        {"name": "VGA_640x480", "id": "8"},
        {"name": "SVGA_800x600", "id": "9"},
        {"name": "UXGA_1600x1200", "id": "13"}
    ]

    res_results = {}
    for r in resolutions:
        print(f"\n--- Testing Resolution: {r['name']} (id={r['id']}) ---")
        set_control("framesize", r["id"])
        time.sleep(1.5)

        print("  Running Still Capture Benchmark (3 samples)...")
        still_data = benchmark_still(r["name"], count=3)
        print(f"    Avg Latency: {still_data['avg_latency_s']}s (Min: {still_data['min_latency_s']}s, Max: {still_data['max_latency_s']}s) | Avg Size: {still_data['avg_size_bytes']} bytes")

        print("  Running Live MJPEG Stream Benchmark (5.0s)...")
        stream_data = benchmark_stream(r["name"], duration=5.0)
        print(f"    Frames: {stream_data['frames_received']} | FPS: {stream_data['fps']} | Bandwidth: {stream_data['throughput_kb_s']} KB/s | Avg Frame: {stream_data['avg_frame_kb']} KB")

        post_status = get_status()
        res_results[r["name"]] = {
            "resolution_id": r["id"],
            "still_capture": still_data,
            "mjpeg_stream": stream_data,
            "heap_free": post_status.get("free_heap"),
            "psram_free": post_status.get("free_psram"),
            "rssi": post_status.get("wifi_rssi")
        }

    # Restore default VGA resolution & motion detection
    print("\nRestoring default framesize=8 (VGA) & enableMotion=1...")
    set_control("framesize", "8")
    set_control("enableMotion", "1")
    time.sleep(1)

    print("\n--- Running Web Server Concurrency Stress Test ---")
    stress_data = stress_test_webserver(n_requests=10, workers=5)
    print(f"  Results: {stress_data['success_rate_pct']}% success across {stress_data['total_requests']} concurrent requests")
    print(f"  Avg Request Latency: {stress_data['avg_req_latency_s']}s")

    final_status = get_status()

    report = {
        "timestamp": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
        "device": {
            "ip": BASE_URL,
            "firmware_version": initial_status.get("fw_version"),
            "camera_model": initial_status.get("camModel"),
            "mac_address": initial_status.get("macAddressWiFi"),
            "storage_fs": initial_status.get("card"),
            "storage_used": initial_status.get("used_bytes"),
            "storage_free": initial_status.get("free_bytes"),
            "storage_total": initial_status.get("total_bytes")
        },
        "resolution_benchmarks": res_results,
        "concurrency_stress_test": stress_data,
        "stability_metrics": {
            "initial_heap": initial_status.get("free_heap"),
            "final_heap": final_status.get("free_heap"),
            "initial_psram": initial_status.get("free_psram"),
            "final_psram": final_status.get("free_psram"),
            "wifi_rssi": final_status.get("wifi_rssi"),
            "uptime": final_status.get("up_time")
        }
    }

    with open(OUTPUT_JSON, "w") as f:
        json.dump(report, f, indent=2)

    print(f"\nBenchmark successfully completed! Metrics saved to {OUTPUT_JSON}")

if __name__ == "__main__":
    main()
