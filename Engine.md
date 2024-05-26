# Core    
| CLASS | DESCRIPTION |
| :---  | :---  |
| Engine | A Singleton, the core of the project <br> Handles the program window and render target <br> Keeps an instance of: <br> - Entity Handler <br> - Gui Handler <br> - Console   |
| Console | A datalogging implementation in ImGui  |

# Handlers/Managers  
| CLASS | DESCRIPTION |
| :---  | :---  |
| EntityHandler | Handles all entities that should be drawn in the render target |
| GuiHandler | Handles all containers functions that should be drawn in the screen |

# GUI/Interface  
| CLASS | DESCRIPTION |
| :---  | :---  |
| Config | A classs that hold global data. <br> Used to manipulate data via ImGui. <br> Used to data access in other classes. <br> |
| EditorContainer | The engine editor GUI <br> Provides real time interactions |
| GameContainer | The game view port when in editor mode |

# Generics/Templates   
| CLASS | DESCRIPTION |
| :---  | :---  |
| Entity | The base class of structures to be rendered |
| Container | The base class of GUIs |
