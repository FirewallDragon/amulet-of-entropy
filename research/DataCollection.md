# Data Collection


I created a special "data collection mode" for the badge to collect raw integer data from each of the main sensor types. Basically, you select the sensor you want to sample from and then let it gather a bunch of readings. It dumps the reading to the serial console, where you can copy and paste them into a file for further analysis.

Speaking of which, see the companion doc: [Data Analysis](DataAnalysis.md)


# Code Changes

I considered creating a separate branch for this work, but the only source file that really needs to change is the main `amulet.ino` file. I could have tried to make this a special mode that's activated with a button sequence, but decided against that, too. Keep it simple and don't pollute the main code for this.

## Amulet Code

I mainly changed the code in `amulet.ino`, but I also added a new method in the `ledstrip` code for the 8-LED progress meter. I went ahead and submitted that new method to the main code. So the only code left that you need to change is the `amulet.ino` file.

If you want to play around with the data collection mode yourself, just copy the `amulet.ino` file in this directory on top of the real one under `/src/amulet`. Then compile and upload to your badge, as usual. That will put your badge in a "data collection mode". See below for instructions on how to use that mode.

## Python Scripts and Data

I did all the data processing using python scripts, which are in this directory:

* `process_raw_data.py`: Converts the comma-separated output from the serial monitor console to the JSON format used by the next script.
* `analyze_data.py`: Takes the `data.json` file and generates a series of data plots, showing the histogram and cumulative distribution function (CDF) of each dataset in the JSON file.
* `data.json`: This is the data I collected from my badge and used for the presentation. See below for details on this data and how I generated it.


# Hardware Specs

The specs on the RP2040-Zero (CPU) can be found [here](https://www.waveshare.com/wiki/RP2040-Zero).


Here are sensors I used and the dataset names I gave them in the code:

|Name|D/A|Bits|Specs|Output|Description|
|---|---|---|---|---|---|
|temp|analog|12|[TMP36GRTZ](https://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf)|ADC, pin 29|temp sensor, SMD chip|
|light|analog|12|[GL10528](https://www.futurlec.com/Datasheet/PHOTOCELL10-14.pdf)|ADC, pin 27|GL10528 Photo Resistor|
|shot|analog|12|[tutorial](http://robseward.com/misc/RNG2/)|ADC, pin 28|Semiconductor Avalanche Noise circuit
|motion|digital|16|[GY-521 Module](http://www.haoyuelectronics.com/Attachment/GY-521/mpu6050.pdf)|"GyX" value|MPU6050 3-Axis Acceleration Gyroscope|
|accel| digital |16|[GY-521 Module](http://www.haoyuelectronics.com/Attachment/GY-521/mpu6050.pdf)|"AcX" value|MPU6050 3-Axis Acceleration Gyroscope|

**Note 1:** The RP2040 `analogRead()` function will return 16-bit values, but it's only capable of 12 bits of resolution on the RP2040-Zero. Note also that, by default, it only reports 10 bits of resolution. We can bump this up to the max by calling `analogReadResolution(12)`. The most significant 4 bits will always be `0`. See [here](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) and [here](https://www.arduino.cc/reference/en/language/functions/zero-due-mkr-family/analogreadresolution/) for details.

**Note 2:** The 3-transistor "shot" circuit is meant to return binary values. You find the mean of the analog output distribution, and then use that level to decide if the output is a `0` or `1` based on whether the measured value is less than or greater than the mean. I didn't actually do that... I just used the source as pure analog noise.

# Using Data Collection Mode

It's pretty simple. When you start up, it waits for you to open the serial port monitor. This is because all the data will be output to the serial port console window. So if it's sitting there saying "Waiting for serial..." then you need to open the serial port console window on the Arduino IDE.

Then you're given a choice of mode, starting at "motion". Using the **Plus/Minus** buttons you can select your mode (ie, which sensor you want to use). The names match the table above.

Once you're on the mode you want, click **Select** to start collecting data. It will give you 5 seconds, in case you want to set it down and walk away, or prepare is some other way. The badge will sample the sensor and dump the values to the console in hexidecimal form, separated by commas.

Click **Back** to interrupt the data collection.

The code as written will generate 10,000 samples. You can change this, just look in the code for:

`const int SAMPLES = 10000;`

## Using the Data

Copy and paste the console output (just the lines containing comma-separated hex data) to a file. Save the data to a text file with the form `<dataset-name>.data`, where "dataset-name" is a simple string that will be used to identify the set of data. For example, for the passive light data, I used the string "light_passive".

Put all of your `.data` files into a directory, then run the `process_raw_data.py` script on it to generate your own `data.json` file. The `process_raw_data.py` script takes one argument: the directory holding the `.data` files.

## Reference Data

Note that I separately generated a set of 10,000 samples of uniformly-distributed random data that I added to my own `data.json` file for reference, cleverly labeled "reference". I just did something like the below and added it to the JSON data.

```lang-python
import random
import numpy as np

ref = []
for i in range(10000):
    ref.append(np.random.randint(2**16))
```

# Perturbing the Environment

For all but the shot values, I took two sets of data:

* a "passive" (baseline) set where I tried *not* to perturb the environment
* an "active" set where I tried to vary the environment for the given sensor

I'm not sure if it's possible to influence the avalanche noise in the shot circuit and frankly I didn't bother trying to find out.

Here's what I did with the other sensors...

## Passive

The passive mode should be the "nearly worst case" scenerio, where there's minimal fluctuation in the measurements.

* **motion/accel**: I left the device just sitting on the table while I sat perfectly still nearby. I even tried to keep noise to a minumum.
* **light**: I had some lights on, but nothing that flashed or changed. (Note that there's a 60Hz fluctuation from the power line. I didn't try to do anything about that.) My nearby monitor was showing a fixed image (no moving content).
* **temp**: The badge was sitting still on a table, with no obvious air currents blowing across it. Temp should be basically static.

## Active

For this mode, I tried to vary the environmental conditions, without going crazy.

* **motion/accel**: I gently rotated the badge with my hand, trying to vary the speed a bit here and there. I say 'gently' because when I moved it too fast, it seemed to overload it. When that happened, the gyro output a fixed value (`0x8000`) which skewed the data.
* **light**: I alternated flashing a bright flashlight on the sensor (light) and covering the sensor with my hand (dark).
* **temp**: This was trickier. I alternated spraying it with compressed air (which gets cold) and a heat gun.

# Misc Notes

1. I could have collected the data into an array in memory, but honestly this ate a lot of RAM. So I just printed the values to the serial port, then copied and pasted the values into files. It wasn't really that much slower to do it this way.
1. The analog sensor readings are only 12 bits in depth, even though the A2D output is a 16-bit integer. See the specs on the microcontroller's analog inputs.
2. There are actually two temp sensors on this badge. The motion processing unit has a temp sensor in it, but I didn't use it.
3. I decided that 10,000 samples was good enough to establish a distribution. This thing isn't that fast, so waiting for the data is a pain. But it's especially hard when perturbing the environment. (See next point.)