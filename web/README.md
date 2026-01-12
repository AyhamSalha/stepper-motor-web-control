# Web Interface

This folder contains the editable HTML source files for the stepper motor web interface.

## Structure

```
web/
├── index/
│   ├── index.html - Start page with the initial "Start" button
│   └── style.css  - Styles for the start page
├── input/
│   ├── input.html - Parameter input form (distance, rounds, speed)
│   ├── style.css  - Styles for the input form
│   └── script.js  - JavaScript for slider value updates
└── stop/
    ├── stop.html  - Motor running page with stop button
    └── style.css  - Styles for the stop page
```

## Development Workflow

1. Edit the HTML, CSS, and JS files in their respective folders
2. Test them by opening the HTML files directly in a browser
3. When ready, update `firmware/include/webpages.h` with the changes
4. Rebuild and upload the firmware

## Note

These files are for development and documentation. The actual web pages served by the ESP32 are embedded in the firmware at compile time from `webpages.h`.
