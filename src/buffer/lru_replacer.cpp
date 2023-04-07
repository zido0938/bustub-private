//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_replacer.cpp
//
// Identification: src/buffer/lru_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/lru_replacer.h"

namespace bustub {

LRUReplacer::LRUReplacer(size_t num_pages) {}

LRUReplacer::~LRUReplacer() = default;

bool LRUReplacer::Victim(frame_id_t *frame_id) {
	lru_mutex.lock();
	if(!unpinned_frames.empty()){
		*frame_id=unpinned_frames.front();
		unpinned_frames.pop_front();
		lru_mutex.unlock();
		return true;
	}
	lru_mutex.unlock();
 	return false; 
}

void LRUReplacer::Pin(frame_id_t frame_id) {
	lru_mutex.lock();
	for(std::list<frame_id_t>::iterator iter = unpinned_frames.begin(); iter != unpinned_frames.end(); iter++){
		if(*iter==frame_id){
			unpinned_frames.erase(iter);
			break;
		}
	}
	lru_mutex.unlock();
}

void LRUReplacer::Unpin(frame_id_t frame_id) {
	lru_mutex.lock();
	bool exist_flag = false;
	for(std::list<frame_id_t>::iterator iter = unpinned_frames.begin(); iter !=unpinned_frames.end(); iter++){
		if(*iter==frame_id){
			exist_flag=true;
			break;
		}
	}
	if(!exist_flag){
		unpinned_frames.push_back(frame_id);
	}
	lru_mutex.unlock();
}
size_t LRUReplacer::Size() { return unpinned_frames.size(); }

}  // namespace bustub
