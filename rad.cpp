#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>
#include "Heap.h"
#include "PriorityQueue.h"
using namespace std;

Heap create_heap2() {
	int m, len, elem, steps;
	Heap heap2;
	do {
		cout << "Unesite m: ";
		cin >> m;
	} while (m < 1);
	heap2.init(m);
	do {
		cout << "Unesite duzinu: ";
		cin >> len;
	} while (len < 1);
	for (int i = 0; i < len; i++) {
		cout << "Unesite element: ";
		cin >> elem;
		steps = 0;
		heap2.add(elem, steps);
	}

	cout << "Heap2 koji se dodaje na heap1:" << endl;
	cout << heap2 << endl;

	return heap2;
}

void citanje_iz_datoteke_red(priorityQueue* pq, string filename) {
	ifstream infile;
	infile.open(filename);

	if (!infile.is_open()) {
		cout << "Ne postoji zadati file!\n";
		return;
	}
	string num_string;

	while (getline(infile, num_string)) {
		pq->push(stoi(num_string));
	}

	infile.close();
}

void pravljenje_red_random(priorityQueue* q) {
	int low, high, len, num;
	int steps = 0;
	do {
		cout << "Unesite duzinu: ";
		cin >> len;
	} while (len < 1);

	cout << "Unesite donju granicu: ";
	cin >> low;
	do {
		cout << "Unesite gornju granicu: ";
		cin >> high;
	} while (high <= low);


	for (int i = 0; i < len; i++) {
		num = (rand() % (high - low + 1) + low);
		q->push(num);
	}
}


void citanje_iz_datoteke_heap(Heap* heap, int& steps) {
	ifstream infile;
	string filename;
	cout << "Unesite ime datoteke: ";
	cin >> filename;
	infile.open(filename);

	if (!infile.is_open()) {
		cout << "Ne postoji zadati file!\n";
		return;
	}
	string num_string;

	while (getline(infile, num_string)) {
		heap->add((stoi(num_string)), steps);
	}

	infile.close();
}

void pravljenje_heapa_random(Heap* heap) {
	int low, high, len, num;
	int steps = 0;
	do {
		cout << "Unesite duzinu: ";
		cin >> len;
	} while (len < 1);

	cout << "Unesite donju granicu: ";
	cin >> low;
	do {
		cout << "Unesite gornju granicu: ";
		cin >> high;
	} while (high <= low);


	for (int i = 0; i < len; i++) {
		num = (rand() % (high - low + 1) + low);
		heap->add(num, steps);
	}

}




int main(int argc, char* argv[]) {
	int option1, option11, option21, option22, read;
	int m, elem, steps, newM;
	Heap heap1, heap2;
	priorityQueue pq;

	do {
		cout << "----------MENI----------\n";
		cout << "1. Testiranje heapa\n";
		cout << "2. Testiranje reda\n";
		cin >> option1;
	} while (option1 < 1 || option1 > 2);
	cout << "\n";

	if (option1 == 1) {

		while (1) {
			do {
				cout << endl;
				cout << "1. Inicijalizacija heapa\n";
				cout << "2. Dodavanje elementa u heap\n";
				cout << "3. Dohvatanje minimalnog elementa\n";
				cout << "4. Brisanje minimalnog elementa\n";
				cout << "5. Promena m-arnosti heapa\n";
				cout << "6. Unija heapova\n";
				cout << "7. Ispis heapa\n";
				cout << "8. Brisanje heapa\n";
				cout << "9. Brisanje proizvoljnog kljuca\n";
				cout << "0. Kraj\n";
				cin >> option11;
			} while (option11 < 0 || option11 > 9);


			if (option11 == 1) {
				if (heap1.getInit()) {
					cout << "Heap vec postoji!\n";
				}
				else {
					steps = 0;
					do {
						cout << "Unesite m: ";
						cin >> m;
					} while (m < 1);
					heap1.init(m);

					do {
						cout << "1. Ucitavanje iz datoteke\n";
						cout << "2. Generisanje random kljuceva\n";
						cout << "3. Citanje iz komande linije\n";
						cout << "4. Prazan heap\n";
						cin >> read;
					} while (read < 1 || read > 4);
					
					if (read == 1) {
						steps = 0;
						citanje_iz_datoteke_heap(&heap1, steps);
					}
					else if (read == 2) {
						pravljenje_heapa_random(&heap1);
					}
					else if (read == 3) {

						for (int i = 1; i < argc; i++) {
							heap1.add(atoi(argv[i]), steps);
						}
					}
					else {
						continue;
					}


				}
			}
			else if (option11 == 2) {
				if (heap1.getInit() == false) {
					cout << "Heap ne postoji!\n";
					continue;
				}
				cout << "Unesite novi element: ";
				cin >> elem;
				steps = 0;
				heap1.add(elem, steps);
				cout << "Broj " << elem << " unet!\n";
				cout << "Broj koraka: " << steps << endl;
			}
			else if (option11 == 3) {
				if (heap1.getInit() == false) {
					cout << "Heap ne postoji!\n";
					continue;
				}
				if (heap1.getSize() == 0) {
					cout << "Heap prazan!\n";
					continue;
				}
				cout << "Minimalni element: " << heap1.get() << endl;
			}
			else if (option11 == 4) {
				if (heap1.getInit() == false) {
					cout << "Heap ne postoji!\n";
					continue;
				}
				if (heap1.getSize() == 0) {
					cout << "Heap prazan!\n";
					continue;
				}
				steps = 0;
				elem = heap1.del(steps);
				cout << "Obrisan i dohvacen element: " << elem << endl;
				cout << "Broj koraka: " << steps << endl;
			}
			else if (option11 == 5) {
				if (heap1.getInit() == false) {
					cout << "Heap ne postoji!\n";
					continue;
				}
				do {
					cout << "Unesite novo m: ";
					cin >> newM;
				} while (newM < 1);
				heap1.convertTo(newM);
			}
			else if (option11 == 6) {
				if (heap1.getInit() == false) {
					cout << "Heap ne postoji!\n";
					continue;
				}
				Heap heap2 = create_heap2();
				steps = 0;
				heap1.heapUnion(heap2, steps);
				cout << "Broj koraka: " << steps;
			}
			else if (option11 == 7) {
				if (heap1.getInit() == false) {
					cout << "Heap ne postoji!\n";
					continue;
				}
				cout << heap1;
			}
			else if (option11 == 8) {
				if (heap1.getInit() == false) {
					cout << "Heap ne postoji!\n";
					continue;
				}
				heap1.destroy();
			}
			else if (option11 == 9) {
				if (heap1.getInit() == false) {
					cout << "Heap ne postoji!\n";
					continue;
				}
				if (heap1.getSize() == 0) {
					cout << "Heap prazan!\n";
					continue;
				}
				cout << "Unesite kljuc koji zelite da izbrisete: ";
				cin >> elem;
				heap1.deleteKey(elem);
			}
			else if (option11 == 0) {
				return 0;
			}
		}

	}

	else {
		
	while (1) {

		do {
			cout << "1. Testiranje reda\n";
			cout << "2. Testiranje performansi\n";
			cout << "3. Kraj\n";
			cin >> option21;
		} while (option21 < 1 || option21 > 3);


		if (option21 == 1) {

			while (1) {

				do {
					cout << "1. Stvaranje reda\n";
					cout << "2. Ispitivanje da li je red prazan\n";
					cout << "3. Dohvatanje prvog elementa\n";
					cout << "4. Brisanje prvog elementa\n";
					cout << "5. Umetanje elementa u red\n";
					cout << "6. Vracanje na glavni meni\n";
					cout << "7. kraj\n";
					cin >> option22;
				} while (option22 < 1 || option22 > 7);


				if (option22 == 1) {
					if (pq.is_init()) {
						cout << "Red vec postoji!\n";
						continue;
					}
					do {
						cout << "Unesite m reda: ";
						cin >> m;
					} while (m < 1);

					pq.set_m(m);

					do {
						cout << "1. Citanje iz datoteke\n";
						cout << "2. Random generisanje kljuceva\n";
						cout << "3. Citanje iz komandne linije\n";
						cout << "4. Prazan red\n";
						cin >> read;
					} while (read < 1 || read > 4);

					if (read == 1) {
						cout << "Unesite ime datoteke: ";
						string filename;
						cin >> filename;
						citanje_iz_datoteke_red(&pq, filename);
					}
					else if (read == 2) {
						pravljenje_red_random(&pq);
					}
					else if (read == 3) {
						
						for (int i = 1; i < argc; i++) {
							pq.push(atoi(argv[i]));
						}

					}
					else {
						continue;
					}
				}
				else if (option22 == 2) {
					if (pq.is_init()) {
						if (pq.is_empty()) {
							cout << "Red je prazan!\n";
						}
						else {
							cout << "Red nije prazan!\n";
						}
					}
					else {
						cout << "Red ne postoji\n";
						continue;
					}
				}
				else if (option22 == 3) {
					if (pq.is_init() == false) {
						cout << "Red ne postoji!\n";
						continue;
					}
					if (pq.is_empty()) {
						cout << "Red je prazan\n";
						continue;
					}
					cout << pq.front() << endl;
				}
				else if (option22 == 4) {
					if (pq.is_init() == false) {
						cout << "Red ne postoji!\n";
						continue;
					}
					if (pq.is_empty()) {
						cout << "Red je prazan\n";
						continue;
					}
					cout << "Obrisan kljuc " << pq.pop() << endl;
				}
				else if (option22 == 5) {
					if (pq.is_init() == false) {
						cout << "Red ne postoji!\n";
						continue;
					}
					cout << "Unesite novi element: ";
					cin >> elem;
					pq.push(elem);
				}
				else if (option22 == 6) {
					break;
				}
				else {
					return 0;
				}



			}
		}
		else if (option21 == 2) {

		cout << endl;
		cout << "Velicina reda, m reda\tVreme umetanja\tBroj koraka pri umetanju\tVreme izbacivanja\tBroj koraka pri izbacivanju" << endl;


		for (int i = 100; i <= 100000; i *= 10) {
			for (int j = 2; j <= 8; j *= 2) {

				priorityQueue curr_q;
				curr_q.set_m(j);
				steps = 0;

				if (i == 100) {
					string s = "100, " + to_string(j);
					cout << left;
					cout << setw(24);
					cout << s;


					cout << setw(16);
					auto start = chrono::high_resolution_clock::now();
					citanje_iz_datoteke_red(&curr_q, "test_100.txt");
					auto end = chrono::high_resolution_clock::now();
					chrono::duration<double, milli> time_ellapsed_ms = end - start;
					s = to_string(time_ellapsed_ms.count()) + "ms";
					cout << s;

					cout << setw(32);
					cout << curr_q.getInsSteps();


					cout << setw(24);
					start = chrono::high_resolution_clock::now();
					for (int t = 0; t < i; t++) {
						curr_q.pop();
					}
					end = chrono::high_resolution_clock::now();
					time_ellapsed_ms = end - start;
					s = to_string(time_ellapsed_ms.count()) + "ms";
					cout << s;
					cout << curr_q.getDelSteps();

				}
				else if (i == 1000) {
					string s = "1000, " + to_string(j);
					cout << left;
					cout << setw(24);
					cout << s;


					cout << setw(16);
					auto start = chrono::high_resolution_clock::now();
					citanje_iz_datoteke_red(&curr_q, "test_1000.txt");
					auto end = chrono::high_resolution_clock::now();
					chrono::duration<double, milli> time_ellapsed_ms = end - start;
					s = to_string(time_ellapsed_ms.count()) + "ms";
					cout << s;

					cout << setw(32);
					cout << curr_q.getInsSteps();


					cout << setw(24);
					start = chrono::high_resolution_clock::now();
					for (int t = 0; t < i; t++) {
						curr_q.pop();
					}
					end = chrono::high_resolution_clock::now();
					time_ellapsed_ms = end - start;
					s = to_string(time_ellapsed_ms.count()) + "ms";
					cout << s;
					cout << curr_q.getDelSteps();
				}
				else if (i == 10000) {
					string s = "10000, " + to_string(j);
					cout << left;
					cout << setw(24);
					cout << s;


					cout << setw(16);
					auto start = chrono::high_resolution_clock::now();
					citanje_iz_datoteke_red(&curr_q, "test_10000.txt");
					auto end = chrono::high_resolution_clock::now();
					chrono::duration<double, milli> time_ellapsed_ms = end - start;
					s = to_string(time_ellapsed_ms.count()) + "ms";
					cout << s;

					cout << setw(32);
					cout << curr_q.getInsSteps();


					cout << setw(24);
					start = chrono::high_resolution_clock::now();
					for (int t = 0; t < i; t++) {
						curr_q.pop();
					}
					end = chrono::high_resolution_clock::now();
					time_ellapsed_ms = end - start;
					s = to_string(time_ellapsed_ms.count()) + "ms";
					cout << s;
					cout << curr_q.getDelSteps();
				}
				else if (i == 100000) {
					string s = "100000, " + to_string(j);
					cout << left;
					cout << setw(24);
					cout << s;


					cout << setw(16);
					auto start = chrono::high_resolution_clock::now();
					citanje_iz_datoteke_red(&curr_q, "test_100000.txt");
					auto end = chrono::high_resolution_clock::now();
					chrono::duration<double, milli> time_ellapsed_ms = end - start;
					s = to_string(time_ellapsed_ms.count()) + "ms";
					cout << s;

					cout << setw(32);
					cout << curr_q.getInsSteps();


					cout << setw(24);
					start = chrono::high_resolution_clock::now();
					for (int t = 0; t < i; t++) {
						curr_q.pop();
					}
					end = chrono::high_resolution_clock::now();
					time_ellapsed_ms = end - start;
					s = to_string(time_ellapsed_ms.count()) + "ms";
					cout << s;
					cout << curr_q.getDelSteps();
				}
				cout << endl;
			}
		}
		}
		else {
			return 0;
		}


		}


	}
	

	return 0;
}