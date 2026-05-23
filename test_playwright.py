from playwright.sync_api import sync_playwright
import os

with sync_playwright() as p:
    browser = p.chromium.launch()
    page = browser.new_page()
    pwd = os.getcwd()
    page.goto(f"file://{pwd}/data/MJPEG2SD.htm")
    page.screenshot(path="test.png")
    browser.close()
