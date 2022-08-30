# VtdApi Samples

## ExampleScpVtdControl

Basic VTD and simulation control sample.

Requirements:
- VTD need to be started manually with Standard setup and SampleProject project.
- SCP on port 48179 (default)

## ExampleRdbPrint

ExampleRdbPrint defines - the entry point for the console application. It receives and prints messages from the RDB channel and sends a trigger for the next frame.

Requirements:
- VTD need to be started manually with GroundTruth.headless setup and SampleProject project.
- RDB on TCP port 48190 (default)

## ExampleDriverControl

ExampleDriverCtrl defines - the entry point for the console application and usage of simple driving control. It receives and prints messages from the RDB channel and send simple driver control message. Ego's auto increases speed and decreases based on sine function and simulation time.

## ExampleDriverControlTorque

ExampleDriverCtrlTorque defines - the entry point for the console application and usage of simple driving control.

It receives RDB message, process it, print data to console and send simple driver control message. 

Ego's auto increases and decreases speed, and applies torque based on sine function and simulation time.

## ExampleConsoleProxyPackage

ExampleConsoleProxyPackage defines - the entry point for the console application.

It receives RDB message, process it, print data Proxy to console and send proxy message to VTD. 

## ExampleDriveControl

This sample showing how to use VtdApi with RdbMessages, and simple ACC which breaks when an object has been detect.

Start VTD with Standard setup and Sample project.

Set sensor properties. 

Sample receives RDB message, process it, print driver data to console and breaks when objects is inside sensor range. 

## ExampleDriveControlAdvanced

ExampleDriveControlAdvanced is an example how to use VtdApi to control vehicle.

1. It receives data from sensor,
2. Calculate position of detected object,
3. Check if the object has same direction as Ego,
4. Control ego's vehicle to follow object in front of him to keep same speed and distance.

Start VTD with Standard setup and Sample project.

Set sensor properties. 

## ExampleScpBuilder

Shows basic simulation control with custom scp message to set speed.

Requirements:
- VTD need to be started manually with Standard setup and SampleProject project.

## ExampleScpPrint

Connects to standard SCP Port (48179) and prints all message sent on this channel.

Requirements:
- VTD need to be started manually
- SCP on port 48179 (default)

## ExampleSharedMemory2Png 

Simulation control with sync triggering via RDB and reading SHM buffer.

Enable RDB sync trigger and set SHM keys in your setup.

The numbers should match the numbers in the setups. 

The numbers of SHM keys should match the numbers in the setups. Last parameter should match buffer release flag from setup.

Usage:

Shm2PngDual 2 0x0120a 0x0120b 2

## ExampleTestAutomation

Uses Standard setup and Sample Project and executes different scenarios.

vtdStart.sh requires you to set the VTD_ROOT environment variable.
Assuming VTD is at ~/VTD and you are using bash or zsh:
    
    > export VTD_ROOT=~/VTD

Usage:

    > ./VariationSample $VTD_ROOT
    
Alternatively you can specify an alternative setup:

    > ./VariationSample $VTD_ROOT <setup_name>


## ExampleVehicleDynamicsIntegration

ExampleVehicleDynamicsIntegration is an example how to use VtdApi to fully control vehicle.

It processes object state, calculate dummy object state (only moving object in x direction) and send object state to VTD.

Start VTD with Standard setup and Sample project.

## ExampleVehicleDynamicsIntegrationUDP

ExampleVehicleDynamicsIntegrationUDP is an example how to use VtdApi to fully control vehicle.

It processes object state, calculate dummy object state (only moving object in x direction) and send object state to VTD.

Start VTD with Standard.UDP setup and Sample project.

## ExampleVtdRemoteControl

Full automation, uses different Setups and starts and stops each of them.

vtdStart.sh requires you to set the VTD_ROOT environment variable.

Assuming VTD is at ~/VTD and you are using bash or zsh:

    > export VTD_ROOT=~/VTD

Usage:
    
    > ./VariationSample $VTD_ROOT
