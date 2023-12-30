# CABLESHIELDTESTINATOR

Recently a [post](https://www.instagram.com/audio.pilz/p/CvVS7SXtaue/) by AudioPilz inspired me to work on a device that non-invasively detects whether a cable is shielded or not. From an economic point of view this device makes absolutely no sense. It was a just-for-fun project to find out whether it can be done or not. Once again I learned a lot.

Cheap audio patch cables often come unshielded. That means that the second conductor (ground, the shield) is not a mesh of wires wrapped around the signal conductor (as I would expect it from cables for audio). Instead there are just two wires lying next to each other inside the coating. So I wanted to find out if it was possible to build a device that could determine whether a cable was shielded or not without cutting it. 

![cables](images/cables.png)

## The Idea

The idea was to put the cable through a coil, run signals through both conductors alternating and measure the response that gets induced in the coil. 

![Block  diagram](images/blockdiagram.png)

A cable with two equal conductors (unshielded) should behave different from a cable where one conductor is wrapped around the other one (shielded). It turned out that this approach oviously was good enough to separate shielded cables from unshielded ones.

<img src="images/photo1.jpg" width="400"><img src="images/photo2.jpg" width="400">

## Circuit Diagram

The cicruit uses a TL084 as an oscillator to generate a triangular waveform at about 250 Hz. An ATMEGA328p microcontroller uses two relays to pass this signal through this or that conductor of the cable which is placed inside a coil, inducing weak signals in the coil. The coil itself is connected to another TL084 to amplify and smooth these signals. Finally, the microcontroller reads the analog signal and evaluates it.

![Block  diagram](images/schematic.png)

## The Code

The microcontroller rotates through the four possible states of the two relays and measures the voltage received by the coil. Larger differences between the four options indicate a shielded cable, similar values indicate an unshielded cable.

## The Case

I designed the case myself and printed it with my own 3D printer. I used recycled filament from [Recycle Fabrik](https://recyclingfabrik.com) to reduce plastic waste.

## Contact 

If you like my work and want to contact me for hardware- or software-related projects, head over to https://seige.digital









