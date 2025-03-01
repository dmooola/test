#include "sequence.h"
#include <cassert>  // For assert

namespace main_savitch_3
{
    // CONSTRUCTOR
    sequence::sequence()
        : used(0), current_index(0) {}

    // MODIFICATION MEMBER FUNCTIONS
    void sequence::start() {
        if (used > 0) {
            current_index = 0; // Reset the current index to the start of the sequence
        }
    }

    void sequence::advance() {
        assert(is_item()); // There should be a current item to advance
        if (current_index < used - 1) {
            current_index++; // Move to the next item
        }
        else {
            current_index = used; // If at the end, there's no current item anymore
        }
    }

    void sequence::insert(const value_type& entry) {
        assert(used < CAPACITY); // Ensure there's space in the sequence
        if (is_item()) {
            // Shift elements right to make room for the new element at current_index
            for (size_type i = used; i > current_index; --i) {
                data[i] = data[i - 1];
            }
            data[current_index] = entry; // Insert new element
        }
        else {
            // If there's no current item, insert at the beginning
            for (size_type i = used; i > 0; --i) {
                data[i] = data[i - 1];
            }
            data[0] = entry;
            current_index = 0; // The new item is now the current item
        }
        used++; // One more element in the sequence
    }

    void sequence::attach(const value_type& entry) {
        assert(used < CAPACITY); // Ensure there's space in the sequence
        if (is_item()) {
            // Insert after the current item
            current_index++;
            for (size_type i = used; i > current_index; --i) {
                data[i] = data[i - 1];
            }
            data[current_index] = entry;
        }
        else {
            // If there's no current item, add at the end
            data[used] = entry;
            current_index = used; // The new item becomes the current item
        }
        used++; // One more element in the sequence
    }

    void sequence::remove_current() {
        assert(is_item()); // There should be a current item to remove
        for (size_type i = current_index; i < used - 1; ++i) {
            data[i] = data[i + 1]; // Shift elements left to fill the gap
        }
        used--; // One less element in the sequence
        if (current_index >= used) {
            current_index = used; // If we removed the last element, there's no current item
        }
    }

    // CONSTANT MEMBER FUNCTIONS
    sequence::size_type sequence::size() const {
        return used; // Return the number of elements in the sequence
    }

    bool sequence::is_item() const {
        return current_index < used; // True if there's a current item
    }

    sequence::value_type sequence::current() const {
        assert(is_item()); // There should be a current item to get its value
        return data[current_index]; // Return the current item's value
    }
}

