# VariablesDebugger

**VariablesDebugger** is a plugin for Unreal Engine that lets you inspect and tweak `UPROPERTY` values on actors in real time. It was created to solve a workflow problem and to gain experience with Unreal tools development.


## Features

- 🔧 **Live Variable Editing** – Change `UPROPERTY` values during PIE (Play In Editor) without restarting.
- 🧩 **Flexible UI Setup** – Map `UPROPERTY`s on a class to custom widgets using a simple settings object.
- 💡 **Extensible** – Add your own custom widgets to handle property types however you see fit.

## How It Works

You define which widget should be used for each property by setting up mappings in the plugin settings. This gives you full control over the UI and lets you tailor it to your project's needs.

**Under the Hood:**

- A collection of functions, simple UI widgets, and a central data controller.
- Functions query property information from an actor or class.
- The central data controller processes value changes from widgets and propagates them to the correct actor(s).

## Getting Started

1. Clone this repo or download it as a ZIP.
2. Place it in your project’s `Plugins` folder.
3. Enable the plugin in your project settings.
4. Start PIE and open the Variables Debugger window.
5. Select an actor to see and edit the properties you've configured.

## Extending It

To support custom types or override default widgets, register your own widgets in the settings using the provided config structure. You can build them in Blueprint or C++. **Note:** You must inherit from `UVariablesDebuggerPropertyWidget`.

## Contributing

This is a personal tool, but if it’s useful to you and you have suggestions or improvements, feel free to open an issue or PR.

## License

MIT – free to use and modify.