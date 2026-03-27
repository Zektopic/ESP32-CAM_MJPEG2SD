## 2024-03-18 - [Auth Bypass in webServer.cpp]
**Vulnerability:** Several endpoints like /status, /control, and WebDAV lacked authentication checks, even if HTTP Basic Auth was configured and enabled.
**Learning:** Endpoints were added without explicitly calling the `checkAuth(req)` function that was present for the index endpoint, leading to an auth bypass vulnerability for the remaining endpoints.
**Prevention:** Make sure `checkAuth(req)` is applied consistently across all endpoints or use middleware to enforce authentication rules for sensitive endpoints.
