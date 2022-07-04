#ifndef ENTROPYPOOL_H
#define ENTROPYPOOL_H

/*
=======================================================================================
    The entropy pool holds and manages the incoming noisy data.

    NOTE: I'll be updating this soon to actually do some 'whitening' of the noise
    data, once I figure out what the distribution looks like. See the docs for more
    info on this design and planned changed.
=======================================================================================
*/

#include <queue>
#include <inttypes.h>

// I kept this low on purpose, so the user can see the pool fill and empty.
// If you find this annoying, you can increase this.
const int MAX_POOL_SIZE = 50;


class EntropyPool
{
    public:
        static EntropyPool& get_instance()
        {
            static EntropyPool instance;
            return instance;
        }

        bool is_full();
        bool is_empty();
        int percent_full();
        int size();
        bool accepting_data();

        void harvest_entropy(unsigned int noise);
        int random_int(int max_val);

    private:
        EntropyPool() {};
        EntropyPool(EntropyPool const&);
        void operator=(EntropyPool const&);

        void push_entropy(unsigned int);
        unsigned int pop_entropy();

        std::queue<unsigned int> _pool;
        int max_pool_size = MAX_POOL_SIZE;
        int _accepting_data = true;

        int bytes_harvested = 0;
        int32_t random_value = 0;
};

#endif // ENTROPYPOOL_H