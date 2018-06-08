# SideScroller Camera Plugin for UE4
SideScroller Camera Plugin for Unreal Engine 4

Note that this plugin is still in a very early stage and in heavy developement.

FAQ: Why is nothing updated?

Due to my work on two different projects, all my developing time is floating into these two things. But on the bright side, the camera was updated in the process a lot and as soon as i have time, at the latest at end if july, this plugin will be updated and a lot of buggy functions, more features and cleaner code will be pushed into this plugin.

Things in place:
* Most of camera starting settings
* First Settings are updated when overlapping with viable Actors with SSCOverlapComponent
* Basic manual camera movement
* Different Camera types (static, follow, cylindrical, spline)


Furthermore planned things for v0.1 release:
* Update camera settings when actors with FollowComponent overlapping with viable Actors with OverlapComponent
* Integrate Multiplayer including one Screen and Splitscreen
* Option for ignoring axis movement of actors (e.g. for ignore jumping)
* Integrate x,y,z-Axis limitations (e.g. for hidden rooms or level-endings)
* Replace SSCGameMode with SSCSystemManager for delegating Events so you can use this Plugin with every Gamemode
* Establish naming conventions for c++ files
* Implement automated Testing
* Create a Wiki
* Update the plugin to the newest UE4-version
* Clean up most of the code and add comments
* Clean up and order public variables on components
* Clean up SSCLog Messages and stop spamming Logs
* Optional automatic camera movement when followed actor is not visible for the camera due to opstacles between followed actor and camera (option for one followed actor only)

"Ongoing": Update Example Map and Wiki with implemented features

## Adding The Plugin

1. Close the Unreal Editor.
1. Copy the SideScrollerCameraPlugin folder to Plugins folder next to your .uproject file.
1. Start the Unreal Editor.
1. Enable the plugin in Edit > Plugins > SideScrollerCameraPlugin.

## Usage

1. Create a player pawn without a camera or blend over to the Side Scrolle Camera for example in the Level Blueprint and add Side Scroller Follow Component to the player pawn.
1. Add the Side Scroller Camera to your level.
1. Set Up the Side Scroller Camera with your settings.
1. For Follow-Settings: Put the Side Scroller Follow Component on every actor you wish to follow with the camera.

## Known Issues
* Manual Camera Rotation Offset, especially with slow interpolation-speed

## License

Side Scroller Camera Plugin for Unreal Engine 4 is dual-licensed:

* everything beneath Source\SideScroller\Content\StarterContent is governed by the [Unreal® Engine End User License Agreement](https://www.unrealengine.com/eula) 
* everything else is released under the MIT License
