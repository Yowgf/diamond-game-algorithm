// ALG1-TP2 project appliance file
// Diamonds module
// dynamic algorithm class
// ====================================
//
// Description:
// This class implements the algorithm for finding the minimum
//   diamond waste possible in a sequence of cuts, using a
//   dynamic programming algorithm aproach.
////////////////////////////////////////////////////////////////

#include "Diamonds/dynamic.hpp"

#include <iostream>
#include <stdexcept>

namespace Diamonds {

//:D
// Implements simple insertion sort, to order the diamond weights, 
//   as is needed by our algorithm.
void dynamic::insertion_sort(wvec* p_weights)
{
	std::cerr << "Entering dynamic::insertion_sort" << std::endl;

	if (p_weights == nullptr)
		throw std::invalid_argument("Invalid argument dynamic::insertion_sort p_weights nullptr");
	else if (p_weights->size() <= 1)
		return;

	// Let's sort this vector inline!
	wvec* sorted_weights = p_weights;

	// Our iterators
	// Start at second position
	wvec::iterator it = sorted_weights->begin() + 1;
	wvec::iterator ti = it;
	weight temp = 0; // Necessary for swap
	for (; it != sorted_weights->end(); it++, ti = it) {
		temp = *it; // Trying to insert this weight
		while (ti != sorted_weights->begin()) {
			ti--;
			
			// Reached value smaller, let's stop
			if (*ti <= temp)
				break;

			// Swap
			*(ti + 1) = *ti;
			*ti = temp;
			
		}
	}

	// Print resulting vector
	std::cerr << "Printing sorted weights" << std::endl;
	it = sorted_weights->begin();
	for (; it != sorted_weights->end(); it++) {
		std::cerr << *it << ' ';
	}
	std::cerr << std::endl;

	std::cerr << "Leaving dynamic::insertion_sort" << std::endl;

}

//:D
// Diamond cutting process
weight dynamic::cut_diamonds(wbuckets* p_buckets)
{
	std::cerr << "Entering dynamic::cut_diamonds" << std::endl;
	
	if (p_buckets == nullptr)
		throw std::invalid_argument("Invalid argument dynamic::cut_diamonds p_buckets nullptr");


	// Our iterators
	wbuckets::iterator ti = p_buckets->end();
	ti--;
	wbuckets::iterator ti_aux = ti;
	// New bucket, generated every iteration, as a result of 
	bucket* new_bucket = nullptr;

	while (p_buckets->size() > 1) {
		std::cerr << "Buckets" << std::endl;
		std::cerr.width(5);
		std::cerr.flags(std::ios::internal);
		std::cerr << "W";
		std::cerr.width(5);
		std::cerr.flags(std::ios::internal);
		std::cerr << "C" << '\n';
		wbuckets::iterator ti_aux = p_buckets->begin();
		for (; ti_aux != p_buckets->end(); ti_aux++) {
			std::cerr.width(5);
			std::cerr.flags(std::ios::internal);
			std::cerr << (*ti_aux)->first;
			std::cerr.width(5);
			std::cerr.flags(std::ios::internal);
			std::cerr << (*ti_aux)->second << '\n';
		}

		new_bucket = new bucket((*ti)->first, 1);
		std::cerr << "new_bucket->first: " << new_bucket->first << std::endl;
		std::cerr << "new_bucket->second: " << new_bucket->second << std::endl;
		
		std::cerr << "Combining diamonds" << std::endl;
		// Combine this diamond with the one to the left
		ti_aux = ti;
		ti_aux--;

		new_bucket->first = (*ti)->first - (*ti_aux)->first;
		// Remove one of the diamonds in both buckets.
		(*ti_aux)->second--;
		if ((*ti_aux)->second == 0) {
			delete (*ti_aux);
			p_buckets->erase(ti_aux);
			std::cerr << "Removed ti_aux" << std::endl;
		}
		(*ti)->second--;

		// Set the ti_aux to the right place again
		ti_aux = ti;
		if(ti != p_buckets->begin())
			ti_aux--;

		// In case the cut diamond in last bucket is still the
		//   largest, we dont have to move it.
		// Now insert that last bucket in it's new place
		// Moving iterator to correct position
		while(ti_aux != p_buckets->begin() && (*ti_aux)->first > new_bucket->first)
			ti_aux--;
		// But if the bucket with this diamond weight already exists,
		//   we don't have to create a new one.
		if ((*ti_aux)->first < new_bucket->first) {
			ti_aux++;
		}
		if ((*ti_aux)->first == new_bucket->first) {
			(*ti_aux)->second++;
			delete new_bucket; // We don't need to add a bucket!
		}
		else
			p_buckets->insert(ti_aux, new_bucket);

		if ((*ti)->second == 0) {
			delete *ti;
			ti--;
			p_buckets->pop_back();
		}
	}
	weight answer;
	if (p_buckets->front()->second % 2 == 0)
		answer = 0;
	else
		answer = p_buckets->front()->first;

	std::cerr << "Leaving dynamic::cut_diamonds" << std::endl;
	return answer;
}

//:D
wbuckets* dynamic::bucketized(wvec* p_weights)
{
	std::cerr << "Entering dynamic::bucketized" << std::endl;

	if (p_weights == nullptr)
		throw std::invalid_argument("Invalid argument dynamic::bucketized p_weights nullptr");
	wbuckets* buckets = new wbuckets();
	
	wvec::iterator it = p_weights->begin();
	weight bucket_value = *it; // Current bucket's weight
	unsigned int bucket_counter = 0; // Current weight's ocurrences counter
	for (; it != p_weights->end(); it++) {
		if (*it != bucket_value) {
			// Push bucket to buckets list
			buckets->push_back(new bucket(bucket_value, bucket_counter));
			
			// Start creating new bucket
			bucket_value = *it;
			bucket_counter = 1;
		}
		else {
			// Just count!
			bucket_counter++;
		}
		
	}
	// Special addition for the inclusion of last bucket
	buckets->push_back(new bucket(bucket_value, bucket_counter));

	std::cerr << "Printing buckets" << std::endl;
	std::cerr.width(5);
	std::cerr.flags(std::ios::internal);
	std::cerr << "W";
	std::cerr.width(5);
	std::cerr.flags(std::ios::internal);
	std::cerr << "C" << '\n';
	wbuckets::iterator buckets_it = buckets->begin();
	for (; buckets_it != buckets->end(); buckets_it++) {
		std::cerr.width(5);
		std::cerr.flags(std::ios::internal);
		std::cerr << (*buckets_it)->first;
		std::cerr.width(5);
		std::cerr.flags(std::ios::internal);
		std::cerr << (*buckets_it)->second << '\n';
	}
	
	std::cerr << "Leaving dynamic::bucketized" << std::endl;
	return buckets;
}

//:D
// Implements a dynamic programming version of the diamond cut
//   algorithm.
// The idea is to first order the values in increasing order,
//   and then divide each element into buckets by weight
//   (pre-processing).
// Then, always choose the last bucket, empty it on the ground,
//   and reduce that weight by the next bucket. If there is no
//   next bucket, just return that weight.
weight dynamic::run(wvec* p_weights)
{
	std::cerr << "Entering dynamic::run" << std::endl;

	if (p_weights == nullptr)
		throw std::invalid_argument("Invalid argument dynamic::run p_weights nullptr");

	// Pre-processing
	insertion_sort(p_weights);
	wbuckets* buckets = bucketized(p_weights);

	// Cutting diamonds
	weight answer = cut_diamonds(buckets);

	// delete buckets
	if (buckets != nullptr) {
		while(!buckets->empty()) {
			delete buckets->front();
			buckets->pop_front();
		}
	}
	delete buckets;

	std::cerr << "Leaving dynamic::run" << std::endl;
	return answer;
}

}
