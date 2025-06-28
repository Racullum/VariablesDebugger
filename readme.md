# VariablesDebugger
A plugin for Unreal Engine that lets you change `UPROPERTY` values on actors during runtime. It was created to help my development of another project and gain experience in tool development using Unreal C++.

![
](VariablesDebuggerMovementSpeed60frames.gif)
  - **Live Variable Editing** – Change `UPROPERTY` values during PIE (Play In Editor) without restarting.
  - **Flexible UI Setup** – Map `UPROPERTY`s to custom widgets using the plugin settings object.
  - **Extensible** – Add your own custom widgets to handle property types however you see fit. Change module's container widget to a custom class.
## Usage ##
![
](VariablesDebuggerSettingsUpdate-0.png)
* "Allowed Class Mappings": Array of classes that gives the plugin access to a list of UPROPERTYs.
* "Property to Widget Map": Add an entry here to select what widget the plugin should spawn for a given actor's UPROPERTY.
* "Module Window Widget": Add the widget which will spawn inside our plugins tab window. This widget is the owner of all the property widgets that are spawned for a selected actor.
## Getting Started

1. Clone this repo or download it as a ZIP.
2. Place it in your project’s `Plugins` folder.
3. Enable the plugin in your project settings.
4. Start PIE and open the Variables Debugger window under **Tools** -> **Debug** -> **Variables Debugger**.
5. Select an actor to see and edit the properties you've configured.

## Extending It

To support custom types or override default widgets, register your own widgets in the settings using the provided config structure. You can build them in Blueprint or C++. **Note:** You must inherit from `UVariablesDebuggerPropertyWidget`.

## Contributing

This is a personal tool, but if it’s useful to you and you have suggestions or improvements, feel free to open an issue or PR.

## License

MIT – free to use and modify./YourProject/Plugins/VariablesDebugger/
Regenerate project files.



[definition]: diagram.png
