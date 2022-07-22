# Setup

This is a [HackerBoxes](https://hackerboxes.com/) project, so first and foremost, you need to buy [Box #0080](https://hackerboxes.com/products/hackerbox-0080-entropy). (Note: these things go quickly and when they're gone, they're gone. Don't wait.)

There are three main steps here:

1. Download the Ardiono IDE and install the support packages.
2. Pull the code from this repo and upload the `/data` directory to your device (which contains all the images).
3. Compile and upload the sketchbook to the Amulet of Entropy.
4. (Optional) Add a battery pack.

# Step 1: Arduino IDE Setup

Download and install the Arduino IDE. I used [IDE v1](https://docs.arduino.cc/software/ide-v1) as IDE v2 wasn't quite ready.

Then install v2.x of the [Raspberry Pi Pico/RP2040 Board Manager](https://github.com/earlephilhower/arduino-pico/) (*not* the latest version!). There's a [compiler issue](https://github.com/FirewallDragon/amulet-of-entropy/issues/1) when using the latest version of the Pico board manager. I used version 2.0.3 and have verified that the code will compile with v2.2.2.

1. Pico board manager. Under Prefs > Additional Boards Manager URLs, add:  `https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json`
2. Tools > Board: "xxxxx" > Boards Manager. Search for "pico" and install "Raspberry Pi Pico/RP2040" by Earle F Phillhower, III. Again, do NOT use the latest version! Use v2.2.2.
3. Tools > Board: "xxxxx" > Raspberry Pi RP2040 Boards > Raspberry Pi Pico


## IDE Libraries

You'll need to [install these Arduino IDE libraries](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries). I've noted the versions of them that I am currently using, for what that's worth.

* [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) (v1.10.5)
* [GFX Library for Arduino](https://github.com/moononournation/Arduino_GFX) (v1.2.3)
* [JPEGDEC](https://github.com/bitbank2/JPEGDEC) (v1.2.6)


## Install LittleFS IDE Plugin

This is required to show the images. See the instructions on the [arduino-pico-littlefs-plugin repo](https://github.com/earlephilhower/arduino-pico-littlefs-plugin).

**NOTE!** Once you have LittleFS plugin installed for the Arduino IDE, be sure to set the file system partitioning to give you file space on the board. To do this:

1. With the board attached and the serial monitor NOT open...
2. (IDE) Tools > Flash Size "xxxxx" > 2MB (Sketch: 1MB, FS: 1MB)

If you don't do this, you'll get an error like:

```
> [LittleFS] data    : /<path>/data
> [LittleFS] size    : 0KB
> [LittleFS] page    : 256
> [LittleFS] block   : 4096
> littlefs/lfs.c:561:error: No more free space 0
```

# Step 2: Clone Repo, Upload Images

1. Pull this Git repo to your local machine:

	`git clone https://github.com/FirewallDragon/amulet-of-entropy.git`

2. Double-click the `src/amulet/amulet.ino` file to load the code.
3. Plug in your Amulet of Entropy using a USB port on your computer or a **powered** USB hub.
4. Compile the code (don't upload it just yet).
5. From the IDE, select "Tools", then "Pico LittleFS Data Upload". This puts the image files on the device's flash.


# Step 3: Upload Sketch to Device

You should be ready to roll at this point! Just compile and upload the sketch. Once it completes, the device splash screen should pop up and the LED lights will chase around.

When it first starts, it will need to build up the pool of entropy (list of random values). It will do this automatically and flash when done. Now it's ready to use! See the [User Guide](UserGuide.md) for what to do with it.

# Step 4 (optional): Battery Pack

To run power this badge on its own, you're going to need some sort of battery. The badge supports LiPo battery charging via the [JST PH 2-Pin connector](https://www.adafruit.com/product/261). I used [one of these 600 mAh packs](https://smile.amazon.com/dp/B091FGPP8F?psc=1), but I had to switch the polarity of the JST cable. I actually cut the wires and resoldered them backward, but apparently you can also pry them out of the JST connector and reinsert them, too.

