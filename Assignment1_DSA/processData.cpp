/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 1 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */
#include "requestLib.h"
#include "dbLib.h"
#define DISTANCE_STOP 0.0
#define MAX_TIME_SIZE 25

struct VRecordNew {
	char id[ID_MAX_LENGTH];
	L1List<VRecord>*  listRecord ;
	//Segtion: Constructor
	VRecordNew() {
		id[0] = '\0';
		listRecord = NULL;
	}
	VRecordNew(char *_id, VRecord rec) {
		strcpy(this->id, _id);
		listRecord = new L1List<VRecord>();
		listRecord->insert(rec);
	}
	/*VRecordNew& operator=(VRecord& rec) {
		strcpy(this->id, rec.id);
		this->listRecord->insert(rec);
		return *this;
	}*/
	//END segtion: Constructor
};

void createNewData(L1List<VRecord>& recList,L1List<VRecordNew>*&recordListNew) {
	L1Item<VRecord> * temp = recList.getFirstPointer();
	while (temp != NULL) {
		L1Item<VRecordNew> * curr = recordListNew->getFirstPointer();
		if (curr == NULL) {
			VRecordNew* newRec = new VRecordNew(temp->data.id, temp->data);
			recordListNew->insert(*newRec);
		}
		else {
			while (curr != NULL) {
				if (strcmp(temp->data.id, curr->data.id) == 0) {
					curr->data.listRecord->insert(temp->data);
					break;
				}
				curr = curr->pNext;
			}
			if (curr == NULL) {
				VRecordNew* newRec = new VRecordNew(temp->data.id, temp->data);
				recordListNew->insert(*newRec);
			}
		}
		//
		temp = temp->pNext;
	}
}
time_t timeStopMax(L1List<VRecord>*_listRecord) {
	time_t timeStop = 0;
	L1Item<VRecord>* temp = _listRecord->getFirstPointer();
	L1Item<VRecord>* point = temp;
	while (temp != NULL) {
		if (temp->pNext == NULL) {
			if (timeStop < temp->data.timestamp - point->data.timestamp) {
				timeStop = temp->data.timestamp - point->data.timestamp;
			}
			temp = temp->pNext;
			continue;
		}
		if (distanceVR(temp->data.x, temp->data.y, temp->pNext->data.x, temp->pNext->data.y) <= DISTANCE_STOP) {
			temp = temp->pNext;
			continue;
		}
		else {
			if (timeStop < temp->data.timestamp - point->data.timestamp) {
				timeStop = temp->data.timestamp - point->data.timestamp;
			}
			point = temp->pNext;
		}
		temp = temp->pNext;
	}
	return  timeStop;
}
time_t timeTransfer(L1List<VRecord>* _listRecord) {
	time_t time = 0;
	L1Item<VRecord>* temp = _listRecord->getFirstPointer();
	while (temp->pNext != NULL) {
		if (distanceVR(temp->data.x, temp->data.y, temp->pNext->data.x, temp->pNext->data.y) > DISTANCE_STOP) {
			time += temp->pNext->data.timestamp - temp->data.timestamp;
		}
		//
		temp = temp->pNext;
	}
	//
	return time;
}

double distanceTransfer(L1List<VRecord>* _listRecord) {
	L1Item<VRecord>* temp = _listRecord->getFirstPointer();
	double distance = 0;
	while (temp->pNext != NULL) {
		double distanceCurr = distanceVR(temp->data.x, temp->data.y, temp->pNext->data.x, temp->pNext->data.y);
		if (distanceCurr > DISTANCE_STOP) {
			distance += distanceCurr;
		}
		//
		temp = temp->pNext;
	}
	return distance;
}

double speedTransfer(L1List<VRecord>* _listRecord) {
	//todo
	return distanceTransfer(_listRecord) / timeTransfer(_listRecord);
}

bool isAlwaysTransfer(L1List<VRecord>* _listRecord) {

	if (_listRecord->getSize() <= 1) {
		return false;
	}
	L1Item<VRecord>* temp = _listRecord->getFirstPointer();
	while (temp->pNext != NULL) {
		double distanceCurr = distanceVR(temp->data.x, temp->data.y, temp->pNext->data.x, temp->pNext->data.y);
		if (distanceCurr <= DISTANCE_STOP) {
			return false;
		}
		//
		temp = temp->pNext;
	}
	return true;
}

double distanceWholeJourney(L1List<VRecord>* ptr) {
	if (ptr->getSize() == 1) {
		return 0;
	}
	double distance = 0;
	L1Item<VRecord> * temp = ptr->getFirstPointer();
	while (temp->pNext != NULL) {
		distance += distanceVR(temp->data.x, temp->data.y, temp->pNext->data.x, temp->pNext->data.y);
		temp = temp->pNext;
	}
	return distance;
}

/// Initialize and Finalize any global data that you use in the program

bool initVGlobalData(void** pGData) {
    // TODO: allocate global data if you think it is necessary.
    /// pGData contains the address of a pointer. You should allocate data for the global data
    /// and then assign its address to *pGData
    return true;
}
void releaseVGlobalData(void* pGData) {
    // TODO: release the data if you finish using it
	/*DuLieuTong* duLieuTong = (DuLieuTong*)pGData;
	delete duLieuTong;*/
}

bool processRequest(VRequest& request, L1List<VRecord>& recList, void* pGData) {
	
	//Segtion: process request
	
	char*_idString = request.code + 3;
	char _reqCopy[REQUEST_CODE_SIZE];
	strcpy(_reqCopy, request.code);
	char *_headerString = strtok(_reqCopy, _reqCopy + 3);
	
	//EndSegtion: process request
	// Flow program
	if (strcmp(_headerString, "CNV") == 0) {
		//todo request CNV
		L1List<VRecordNew> * recordListData = new L1List<VRecordNew>();
		createNewData(recList, recordListData);
		cout << _headerString << _idString << ": " << recordListData->getSize() << endl;

	}
	else if (strcmp(_headerString, "VFF") == 0) {
		//todo request VFF
		cout << _headerString << _idString << ": " <<recList.getFirstPointer()->data.id << endl;
		return true;
	}
	else if (strcmp(_headerString, "VFL") == 0) {
		//todo request VLF 
		cout << _headerString << _idString << ": " << recList.getLastPointer()->data.id << endl;
		//requestVFL(recList);
		return true;
	}
	else if (strcmp(_headerString, "VFY") == 0) {
		//todo request VFY
		VRecord recordFirst;
		if (recList.findRecordFirst(_idString, recordFirst)) {
			cout << _headerString<<_idString<<": "<< recordFirst.y << endl;
			return true;
		}
		else {//not found
			return false;
		}
	}
	else if (strcmp(_headerString, "VFX") == 0) {
		VRecord recordFirst;
		if (recList.findRecordFirst(_idString, recordFirst)) {
			cout << _headerString << _idString << ": " << recordFirst.x << endl;
			return true;
		}
		else {//not found
			return false;
		}
		/*L1List<VRecord>* _listRecordSortId = new L1List<VRecord>();
		if (recList.listIdRecord(_idString, _listRecordSortId, recList)) {
			cout << _headerString << _idString << ": " << _listRecordSortId->at(0).x << endl;
		}
		else {
			return false;
		}*/
	}
	else if (strcmp(_headerString, "VLX") == 0) {
		L1List<VRecord>* _listRecordSortId = new L1List<VRecord>();
		if (recList.listIdRecord(_idString, _listRecordSortId, recList)) {
			cout << _headerString << _idString << ": " << _listRecordSortId->getLastPointer()->data.x << endl;
			_listRecordSortId->printRecordSortId();
			return true;
		}
		else {
		return false;
		}
	}
	else if (strcmp(_headerString, "VLY") == 0) {
		L1List<VRecord>* _listRecordSortId = new L1List<VRecord>();
		if (recList.listIdRecord(_idString, _listRecordSortId, recList)) {
			cout << _headerString << _idString << ": " << _listRecordSortId->getLastPointer()->data.y << endl;
			return true;
		}
		else {
			return false;
		}
	}
	else if (strcmp(_headerString, "VFT") == 0) {
		//todo VFT
		L1List<VRecord>* _listRecordSortId = new L1List<VRecord>();
		if (recList.listIdRecord(_idString, _listRecordSortId, recList)) {
			char time[MAX_TIME_SIZE];
			strPrintTime(time, _listRecordSortId->getFirstPointer()->data.timestamp);
			cout << _headerString << _idString << ": " << time << endl;
			return true;
		}
		else {
			return false;
		}
	}
	else if (strcmp(_headerString, "VLT") == 0) {
		//todo VLT
		L1List<VRecord>* _listRecordSortId = new L1List<VRecord>();
		if (recList.listIdRecord(_idString, _listRecordSortId, recList)) {
			cout << _headerString << _idString << ": " << _listRecordSortId->getLastPointer()->data.timestamp << endl;
			return true;
		}
		else {
			return false;
		}
	}
	else if (strcmp(_headerString, "VCR") == 0) {
		L1List<VRecord>* _listRecordSortId = new L1List<VRecord>();
		if (recList.listIdRecord(_idString, _listRecordSortId, recList)) {
			cout << _headerString << _idString << ": " << _listRecordSortId->getSize() << endl;
			return true;
			//_listRecordSortId->printRecordSortId();
		}
		else {
			return false;
		}
	}
	else if ((strcmp(_headerString, "VCL") == 0)) {
		L1List<VRecord>* _listRecordSortId = new L1List<VRecord>();
		if (recList.listIdRecord(_idString, _listRecordSortId, recList)) {
			L1Item<VRecord>* temp = _listRecordSortId->getFirstPointer();
			double _distance = 0;
			while (temp->pNext != NULL) {
				_distance += distanceVR(temp->data.x, temp->data.y, temp->pNext->data.x, temp->pNext->data.y);
				temp = temp->pNext;
			}
			cout << _headerString << _idString << ": " << _distance << endl;
		}
		else {
			return false;
		}
	}
	else if ((strcmp(_headerString, "VMT") == 0)) {
		//todo request VMT
		L1List<VRecord>* _listRecordSortId = new L1List<VRecord>();
		if (recList.listIdRecord(_idString, _listRecordSortId, recList)) {
			L1Item<VRecord>* temp = _listRecordSortId->getFirstPointer();
			time_t timeTransfer = 0;
			while (temp->pNext == NULL) {
				if (distanceVR(temp->data.x, temp->data.y, temp->pNext->data.x, temp->pNext->data.y) > DISTANCE_STOP) {
					timeTransfer += temp->pNext->data.timestamp - temp->data.timestamp;
				}
				// loop exit
				temp = temp->pNext;
			}
			//char time[MAX_TIME_SIZE];
			//strPrintTime(time, timeTransfer);
			cout << _headerString << _idString << ": " << timeTransfer << endl;
			return true;
		}
		else {
			return false;
		}
	}
	else if ((strcmp(_headerString, "VFS") == 0)) {
		L1List<VRecord>* _listRecordSortId = new L1List<VRecord>();
		if (recList.listIdRecord(_idString, _listRecordSortId, recList)) {
			L1Item<VRecord>* temp = _listRecordSortId->getFirstPointer();
			while (temp->pNext != NULL) {
				if (distanceVR(temp->data.x, temp->data.y, temp->pNext->data.x, temp->pNext->data.y) <= DISTANCE_STOP) {
					cout << _headerString << _idString << ": " << temp->pNext->data.x<<" "<< temp->pNext->data.y << endl;
					return true;
				}
				temp = temp->pNext;
			}
			return false;
		}
		else {// don't find id
			return false;
		}
	}
	else if ((strcmp(_headerString, "VLS") == 0)) {
		L1List<VRecord>* _listRecordSortId = new L1List<VRecord>();
		if (recList.listIdRecord(_idString, _listRecordSortId, recList)) {
			_listRecordSortId->reverse();
			L1Item<VRecord>* temp = _listRecordSortId->getFirstPointer();
			while (temp->pNext != NULL) {
				if (distanceVR(temp->pNext->data.x, temp->pNext->data.y, temp->data.x, temp->data.y) <= DISTANCE_STOP) {
					cout << _headerString << _idString << ": " << temp->data.x << " " << temp->data.y << endl;
					return true;
				}
				temp = temp->pNext;
			}
			return false;
		}
		return false;
	}
	else if ((strcmp(_headerString, "VMS") == 0)) {
		L1List<VRecord>* _listRecordSortId = new L1List<VRecord>();
		if (recList.listIdRecord(_idString, _listRecordSortId, recList)) {
			cout << _headerString << _idString << ": " << timeStopMax(_listRecordSortId)<< endl;
			return true;
		}
		return false;
	}
	else if (strcmp(_headerString, "VAS") == 0) {
		L1List<VRecord>* _listRecordSortId = new L1List<VRecord>();
		if (recList.listIdRecord(_idString, _listRecordSortId, recList)) {
			double sumDistance = 0;
			L1Item<VRecord>* temp = _listRecordSortId->getFirstPointer();
			while (temp->pNext != NULL) {
				sumDistance += distanceVR(temp->data.x, temp->data.y, temp->pNext->data.x, temp->pNext->data.y);
				temp = temp->pNext;
			}
			cout << _headerString << _idString << ": " << sumDistance / (_listRecordSortId->getSize() - 1) << endl;
			return true;
		}
		else {
			return false;
		}
	}
	else if (strcmp(_headerString, "MST") == 0) {
		L1List<VRecordNew> * recordListData = new L1List<VRecordNew>();
		createNewData(recList, recordListData);
		L1Item<VRecordNew>* temp = recordListData->getFirstPointer();
		time_t timeStop = 0;
		while (temp != NULL) {
			time_t timeCurrent = timeStopMax(temp->data.listRecord);
			if (timeCurrent > timeStop) {
				timeStop = timeCurrent;
			}
			temp = temp->pNext;
		}
		cout << _headerString << _idString << ": " << timeStop << endl;
		return true;
	}
	else if (strcmp(_headerString, "CNR") == 0) {
		cout << _headerString << _idString << ": " << recList.getSize() << endl;
	}
	else if (strcmp(_headerString, "MRV") == 0) {
		L1List<VRecordNew> * recordListData = new L1List<VRecordNew>();
		createNewData(recList, recordListData);
		L1Item<VRecordNew>* temp = recordListData->getFirstPointer();
		int countRec = 0;
		char _id[ID_MAX_LENGTH];
		while (temp != NULL) {
			if (temp->data.listRecord->getSize() > countRec) {
				countRec = temp->data.listRecord->getSize();
				strcpy(_id, temp->data.id);
			}
			temp = temp->pNext;
		}
		cout << _headerString << _idString << ": " << _id << endl;
	}
	else if (strcmp(_headerString, "LRV") == 0) {
		L1List<VRecordNew> * recordListData = new L1List<VRecordNew>();
		createNewData(recList, recordListData);
		L1Item<VRecordNew>* temp = recordListData->getFirstPointer();
		int countRec = temp->data.listRecord->getSize();
		char _id[ID_MAX_LENGTH];
		while (temp != NULL) {
			if (temp->data.listRecord->getSize() < countRec) {
				countRec = temp->data.listRecord->getSize();
				strcpy(_id,temp->data.id);
			}
			temp = temp->pNext;
		}
		cout << _headerString << _idString << ": " << _id << endl;
	}
	else if (strcmp(_headerString, "MTV") == 0) {
		L1List<VRecordNew> * recordListData = new L1List<VRecordNew>();
		createNewData(recList, recordListData);
		L1Item<VRecordNew>* temp = recordListData->getFirstPointer();
		char _id[ID_MAX_LENGTH];
		time_t timeMax = 0;
		while (temp != NULL) {
			time_t timeCurr = timeTransfer(temp->data.listRecord);
			if (timeCurr > timeMax) {
				timeMax = timeCurr;
				strcpy(_id, temp->data.id);
			}
			//
			temp = temp->pNext;
		}
		cout << _headerString << _idString << ": " << _id << endl;
	}
	else if (strcmp(_headerString, "MVV") == 0) {
		L1List<VRecordNew> * recordListData = new L1List<VRecordNew>();
		createNewData(recList, recordListData);
		L1Item<VRecordNew>* temp = recordListData->getFirstPointer();
		char _id[ID_MAX_LENGTH];
		double speed = 0;
		while (temp != NULL) {
			double speedCurr = speedTransfer(temp->data.listRecord);
			if (speedCurr > speed) {
				speed = speedCurr;
				strcpy(_id, temp->data.id);
			}
			//
			temp = temp->pNext;
		}
		cout << _headerString << _idString << ": " << _id << endl;
	}
	else if (strcmp(_headerString, "CNS") == 0) {
		L1List<VRecordNew> * recordListData = new L1List<VRecordNew>();
		createNewData(recList, recordListData);
		L1Item<VRecordNew>* temp = recordListData->getFirstPointer();
		int count = 0;
		while (temp != NULL) {
			bool check = isAlwaysTransfer(temp->data.listRecord);
			if (check == true) {
				count++;
			}
			//
			temp = temp->pNext;
		}
		cout << _headerString << _idString << ": " << count << endl;
	}
	else if (strcmp(_headerString, "CAS") == 0) {
		
		L1List<VRecordNew> * recordListData = new L1List<VRecordNew>();
		createNewData(recList, recordListData);
		L1Item<VRecordNew>* temp = recordListData->getFirstPointer();
		double distanceTotal = 0;
		while (temp != NULL) {
			if (temp->data.listRecord->getSize() == 1) {
				temp = temp->pNext;
				continue;
			}
			distanceTotal += distanceWholeJourney(temp->data.listRecord) / (temp->data.listRecord->getSize() - 1);
			temp = temp->pNext;
		}
		cout << _headerString << _idString << ": " << distanceTotal / recordListData->getSize() << endl;
	}
	else if (strcmp(_headerString, "LPV") == 0) {
		L1List<VRecordNew> * recordListData = new L1List<VRecordNew>();
		createNewData(recList, recordListData);
		L1Item<VRecordNew>* temp = recordListData->getFirstPointer();
		char _id[ID_MAX_LENGTH];
		double distance = 0;
		while (temp != NULL) {
			double distanceTemp = distanceWholeJourney(temp->data.listRecord);
			if (distanceTemp > distance) {
				distance = distanceTemp;
				strcpy(_id, temp->data.id);
			}
			temp = temp->pNext;//dadasd
		}
		cout << _headerString << _idString << ": " << _id << endl;
	}
	else if (strcmp(_headerString, "SPV") == 0) {
		L1List<VRecordNew> * recordListData = new L1List<VRecordNew>();
		createNewData(recList, recordListData);
		L1Item<VRecordNew>* temp = recordListData->getFirstPointer();
		char _id[ID_MAX_LENGTH];
		double distance = distanceWholeJourney(temp->data.listRecord);
		strcpy(_id, temp->data.id);
		while (temp != NULL) {
			double distanceTemp = distanceWholeJourney(temp->data.listRecord);
			if (distanceTemp < distance) {
				distance = distanceTemp;
				memset((void*)_id, '\0', ID_MAX_LENGTH);
				strcpy(_id, temp->data.id);
			}
			temp = temp->pNext;
		}
		cout << _headerString << _idString << ": " << _id << endl;
	}
	else if (strcmp(_headerString, "RVR") == 0) {

	}
	else {
		return false;
	}
	//End Flow program
}


