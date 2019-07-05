# MPLAB Digital Power Starter Kit v3 (DPSK3)

Out-Of-The-Box firmware for Microchip Technology's MPLAB Digital Power Starter Kit v3 featuring dsPIC33CK Switched-Mode Power Supply Digital Signal Controller.

This repository holds two very different firmware versions:

## 1) Original Firmware (branches orinial_master, orinial_develop, orinial_hotfix, etc.)  
This original firmware verson is suffering from a number of startup and runtime issues which need to be resolved before product release. 
The initial version was tag-ed with v0.9.0.
All existing issues have been added as **Issues** to this repository and a **Project** has been added to organize the hotfix workflow.

The branching model for the hotfixes still foolows the usual scheme:

* Branch orinial_master  
    this is the branch holding the releases. **Do not commit changes to this branch.**

* Branch orinial_develop  
    this is the test branch where hotfixes are merged into and tested before being merged into __original_master__. 

* Branch orinial_develop  
    each HOTFIX is seperated in its own branch, starting with **orinial_hotfix_ [_issue title_]**  
	
### Please look up work items in **Project DPSK3-Initial Firmware Bugfixes** for details


## 2) New Firmware Version (branches master, develop, feature, etc.)  
As the original firmware has been hot-needled, a more consistent, easier to read and understand firmware version is desired.
The preferred version is to have very basic, well commented single-bit configurations for every peripheral isolated in separated files for each peripheral block.
The state machine should be driven from the main()-loop. 
For simplicity it is desired **not** having any hidden libraries included and **not** using code generation tools like MCC at this point. 
All tools used (e.g. to derive parameters) have to be officially released or at least be publicly available to end-users.

### Please look up work items in **Project DPSK3-Simplistic Firmware** for details
