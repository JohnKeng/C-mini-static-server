# Simple C HTTP Server

A simple HTTP server written in C that serves files from a public directory and listens on a configurable port.

一個用 C 語言編寫的簡單 HTTP 伺服器，從 public 目錄提供文件並在可配置的端口上監聽。

## Features 功能

- Serve static HTML files 提供靜態 HTML 文件
- Configurable port 設置端口

## Requirements 要求

- GCC (or any C compiler) GCC（或任何 C 編譯器）

## How to use 使用方法

### 1. Clone the repository 克隆倉庫

```bash
git clone https://github.com/yourusername/simple-c-http-server.git
cd simple-c-http-server
```

### 2. Compile the server 編譯伺服器

```bash
gcc -o miniserver miniserver.c
```

### 3. Run the server 運行伺服器

```bash
./miniserver
```

### 4. Access the server 訪問伺服器

Open your browser and navigate to http://localhost:8080 打開瀏覽器並訪問 

## Project Structure 項目結構

```plaintext
.
├── miniserver.c      # Source code 源代碼
├── public            # Directory for static files 靜態文件目錄
│   └── index.html    # Example HTML file 示例 HTML 文件
└── README.md         # This file 此文件
```


