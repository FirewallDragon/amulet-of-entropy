# Customizing Your Amulet

Once you have your amulet up and running, you might be interested in making your own mods, which I highly encourage! Note that I won't be accepting many direct [contributions](Contrib.md), so instead I recommend that you just make your modifications locally or [fork the primary repo](https://docs.github.com/en/get-started/quickstart/fork-a-repo). Either way, here are a few notes that might help you.

## Bonus Modes

I'll be adding some additional modes soon, including common D&D dice. Stay tuned! You'll find the bonus images and some code you can copy in the [src/bonus](../src/bonus) directory. I'll also add some other splash screen images you can use.

## Flash Memory Full

Note that the `/data` directory, as it stands, will completely fill the 1MB of flash memory set aside for the LittleFS file system. If you're going to add your own modes, you're probably going to need to delete one of the current modes. (I actually wanted to add several other modes, but ran out of room.) I'd delete either `cards` or `tarot`, as these use up the most space.

## Adding Modes

The most likely customization would be to add a new mode. Again, if you want to use images, you're almost surely going to need to make some room first (see above). If you search the code for one of the existing modes, like `coinFlipOutcomes`, you'll see examples of how to do this and find all the places where you'll need to make changes.

To create a new mode:

1. Enumerate the possible outcomes and number them from 1 to whatever, not skipping any numbers.
1. Find or create images for possible outcome. The images should be basic JPEG format with a resolution of 240x240.
2. Add a new Outcomes map in [src/amulet/outcomes.cpp](../src/amulet/outcomes.cpp). You want to map each numbered outcome with an image file. (Note that the text fields aren't used.)
3. Add an `extern` reference to this map in [src/amulet/outcomes.h](../src/amulet/outcomes.h).
3. Update the list of modes in [src/amulet/statemachine.cpp](../src/amulet/statemachine.cpp).

## Entropy Pool Size

Change the value of the variable `MAX_POOL_SIZE` in [src/amulet/entropypool.h](../src/amulet/entropypool.h) to increase or decrease the size of the pool. If you significantly increase it, you might want to also reduce the delay time near the `gathering_entrop()` call in [src/amulet/amulet.ino](../src/amulet/amulet.ino) main loop.

## LED Effects

If you want the LEDs (dragon eyes and arrow gems) to do different things, look at the `cycle()` and `sparkle()` methods in [src/amulet/ledstrip.cpp](../src/amulet/ledstrip.cpp) for examples. You can either modify these directly or add your own. (If you add your own,  you'll need to modify the header file, too, of course - and then call these methods from within the code somewhere. I recommend calling the methods from the main loop.
