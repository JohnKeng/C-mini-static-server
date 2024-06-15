# Simple C HTTP Server

A simple HTTP server written in C that serves files from a public directory and listens on a configurable port.

C 語言編寫的簡單 HTTP 伺服器，讀 public / *.html 作為網頁

## Requirements

- GCC (or any C compiler) GCC（或任何 C 編譯器）

## How to use

### 1. Clone the repository

```bash
git clone https://github.com/yourusername/simple-c-http-server.git
cd simple-c-http-server
```

### 2. Compile the server

```bash
gcc -o miniserver miniserver.c
```

### 3. Run the server

```bash
./miniserver
```

### 4. Access the server

Open your browser and navigate to http://localhost:8080 打開瀏覽器並訪問 

## Project Structure

```plaintext
.
├── miniserver.c      # Source code
├── public            # Directory for static files
│   └── index.html    # HTML file
└── README.md         
```


