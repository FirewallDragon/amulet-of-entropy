#include "entropypool.h"
#include "utils.h"
#include "fsmlist.hpp"

#include <random>


void EntropyPool::push_entropy(unsigned int val)
{
    if ( !is_full() )
    {
        debug("pushing 0x%08X to pool", val);
        _pool.push(val);
    }
    else {
        log("Pool is FULL!");
    }
    debug("Pool capacity: %d %%", percent_full() );
}

unsigned int EntropyPool::pop_entropy()
{
    unsigned int val = 0;

    if ( !is_empty() )
    {
        val = int(_pool.front()); // get the top value
        _pool.pop(); // delete the top value
        debug("popping 0x%08X from pool", val);
    }

    log("Pool capacity: %d %%", percent_full() );
    return val;
}

int EntropyPool::percent_full()
{
    return ( int( (100.0 * _pool.size()) / MAX_POOL_SIZE) );
}

bool EntropyPool::is_full()
{
    return (_pool.size() >= max_pool_size);
}

bool EntropyPool::is_empty()
{
    return _pool.empty();
}

int EntropyPool::size()
{
    return _pool.size();
}

bool EntropyPool::accepting_data()
{
    /* To demonstrate the filling and emptying of the pool, we'll gather
       input when empty until we're full. Then we'll stop gathering until
       the pool is completely empty again. */

    debug("accepting data: %s (%d)", _accepting_data?"true":"false", _pool.size());

    if (is_full()) {
        _accepting_data = false;
    }
    else if (is_empty()) {
        _accepting_data = true;
    }

    return _accepting_data;
}

void EntropyPool::harvest_entropy(unsigned int value)
{

    if (! accepting_data() ) {
        return;
    }

    // We want noisy values. Let's only look at the lowest 8 bits.
    // We'll concatanate bytes till we reach 32 bits, then add to the pool.

    // NOTE: My research has shown that the lower 8 bits isn't really noisy
    // enough for the shot and light sensors. See the /research directory for
    // more info. I may update this code accordingly, if I have time.

    unsigned int last_byte = value & 0x000000FF;
    debug("harvest_entropy: 0x%02X", last_byte);
    random_value = random_value | (last_byte << (bytes_harvested * 8));
    bytes_harvested = bytes_harvested + 1;
    if (bytes_harvested == 4) {
        push_entropy(random_value);
        bytes_harvested = 0;
        random_value = 0;
    }
}

// Random int between 1 and max_val. This was a conscious design choice.
// Also this is sorta the crux of this whole experiment. I will be updating
// all of this code over the coming months. See docs/Contrib.md.
int EntropyPool::random_int(int max_val)
{
    int val = 0;

    debug("Tapping pool, %d entries remaining", _pool.size());
    if (is_empty()) {
        log("POOL IS EMPTY!!!");
    }
    else
    {
        unsigned int seed = pop_entropy();
        srandom(seed);
        val = (random() % max_val) + 1;
        debug("Random int from 1-%d: %d", max_val, val);
    }

    return val;
}
