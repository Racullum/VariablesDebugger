# VariablesDebugger
A plugin for Unreal Engine that lets you change `UPROPERTY` values on actors during runtime. It was created to help my development of another project and gain experience in tool development using Unreal C++.

![
](VariablesDebuggerMovementSpeed60frames.gif)
The plugin was meant to be used in conjuction with BP and UMG. 
  - **Live Variable Editing** – Change `UPROPERTY` values during PIE (Play In Editor) without restarting.
  - **Flexible UI Setup** – Map `UPROPERTY`s to custom widgets using the plugin settings object.
  - **Extensible** – Add your own custom widgets to handle property types however you see fit. Change module's container widget to a custom class.
  
## Usage 
### *Settings* ###
![
](VariablesDebuggerSettingsUpdate-0.png)
* **Allowed Class Mappings**: 
  * Array of classes that gives the plugin access to a list of UPROPERTYs.
* **Property to Widget Map**: 
  * Add an entry here to select what widget the plugin should spawn for a given actor's UPROPERTY.
* **Module Window Widget**: 
  * The widget which will spawn inside our plugins tab window. This widget is the owner of all the property widgets that are spawned for a selected actor.

### *Property Widget (UVariablesDebuggerPropertyWidget)* ###
![
](VariablesDebuggerPropertyWidgetExample.png)
Extend UVariablesDebuggerPropertyWidget so you can make a visual representation of whatever UPROPERTY you are interested in.
* **On Widget Value Changed**
  * Call this anytime you want to update the value of a widget's associated property.
* **Initialized From Property**
  * This event will fire to tell the widget it now has the most up to date property information.

## Getting Started

1. Clone this repo or download it as a ZIP.
2. Place it in your project’s `Plugins` folder.
3. Enable the plugin in your project settings.
4. Fill in the Variables Debugger Settings.
5. Start PIE and open the Variables Debugger window under **Tools** -> **Debug** -> **Variables Debugger**.
6. Select an actor to see and edit the properties you've configured.
   
## Extending It

To support custom types or override default widgets, register your own widgets in the settings using the provided config structure. You can build them in Blueprint or C++. 

**Note:** You must inherit from `UVariablesDebuggerPropertyWidget` when making a widget for a property but can extend from UUserWidget when making the Module Window Widget.

## Contributing

I wrote this primiarly as a way to learn tools development in Unreal C++. However, if you have improvements feel free to open up an issue/pr! Would love to know where I can improve 
:)


## License

MIT – free to use and modify./YourProject/Plugins/VariablesDebugger/
Regenerate project files.



[definition]: diagram.png
