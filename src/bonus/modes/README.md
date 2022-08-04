# Bonus Mode Images

These are bonus images you can use to create different modes for your Amulet of Entropy! **Note** that the flash memory will already be *totally full* with the default images. You're going to have to make room if you want to have new modes with images. See the [customization](../../../docs/Customize.md) doc for help.

# Example: d20

Let's walk through an example, using some bonus images I've provided for you. For a different project (my [dragon challenge coin](https://d20key.com/#/coin)), I created four different suites of animated GIFs of d20 dice to help people generate random passphrases. You can check them out at [d20key.com](https://d20key.com). 

Using [gifsicle](https://www.lcdf.org/gifsicle/) and [ImageMagick](https://imagemagick.org/), I pulled out the 66th frame of each GIF and overlayed it on a nice wood background, creating four sets of 240x240 JPEGs. 

The general steps for adding a new mode are listed [here](../../../docs/Customize.md) (under "Adding Modes"). At this point, steps 1 and 2 are done for you.

So let's go through the remaining steps, with some actual code. Here's what you need to do:

* Set up the images for your new mode
   * Create directory "d20" under `/data`, next to `/d6` and the other mode dirs.
   * Choose the color of d20 you want to use from the [src/bonus/modes/d20](d20) directory.
   * Copy all 20 images (1.jpg through 20.jpg) to your new `/data/d20` directory.
* In [src/amulet/outcomes.cpp](../../../src/amulet/outcomes.cpp), you're going to want to add lines like the following:

```
OutcomeMap d20Outcomes = {
    {1, Outcome("One", "d20/01.jpg")},
    {2, Outcome("Two", "d20/02.jpg")},
...
    {20, Outcome("Twenty", "d20/20.jpg")}
```

* In [src/amulet/outcomes.h](../../../src/amulet/outcomes.h) at the bottom, add your new OutcomeMap:

```
extern OutcomeMap d20Outcomes;
```

* And finally, add your mode to the list in [src/amulet/statemachine.cpp](../../../src/amulet/statemachine.cpp). (Note that I've removed the tarot mode here, because we have to make room for the new images. Again, see [Customization doc](../../../docs/Customize.md).)

```
static const vector<AmuletMode> modes = {
    AmuletMode("Coin Flip", coinFlipOutcomes),
    AmuletMode("Roll Die", d6Outcomes),
    AmuletMode("Roll d20", d20Outcomes),
    AmuletMode("Pick Card", pickCardOutcomes),
    AmuletMode("Magic 8 Ball", eightBallOutcomes),
};
```
* Be sure to re-flash your `/data` to the device. From the IDE, select "Tools", then "Pico LittleFS Data Upload". This puts the image files on the device's flash.
* Compile your new code and upload to the Amulet.