#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <cmath>
using namespace std;
using namespace std::chrono;

// Selection Sort
void selectionSort(int arr[], int n, int &comp_count, int &swap_count) {
    comp_count = 0;
    swap_count = 0;
    auto start = high_resolution_clock::now();
    
    int i, j, smallest;
    
    for(i = 0; i < n-1; i++) {
        smallest = i;
        for(j = i + 1; j < n; j++) {
            comp_count++;
            if(arr[j] < arr[smallest]) {
                smallest = j;
            }
        }
        if(smallest != i) {
            swap(arr[i], arr[smallest]);
            swap_count++;
        }
    }
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Execution Time (Selection Sort): " << duration.count() << " microseconds\n";
}

// Exchange Sort
void exchangeSort(int arr[], int n, int &comp_count, int &swap_count) {
    comp_count = 0;
    swap_count = 0;
    auto start = high_resolution_clock::now();
    
    for(int i = 0; i < n-1; i++) {
        for(int j = i + 1; j < n; j++) {
            comp_count++;
            if(arr[j] < arr[i]) {
                swap(arr[i], arr[j]);
                swap_count++;
            }
        }
    }
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Execution Time (Exchange Sort): " << duration.count() << " microseconds\n";
}

// Bubble Sort
void bubbleSort(int arr[], int n, int &comp_count, int &swap_count) {
    comp_count = 0;
    swap_count = 0;
    auto start = high_resolution_clock::now();
    
    bool isSorted;
    for(int i = 0; i < n-1; i++) {
        isSorted = true;
        for(int j = 0; j < n-i-1; j++) {
            comp_count++;
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swap_count++;
                isSorted = false;
            }
        }
        if(isSorted) break;
    }
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Execution Time (Bubble Sort): " << duration.count() << " microseconds\n";
}

// Insertion Sort
void insertionSort(int arr[], int n, int &comp_count, int &swap_count) {
    comp_count = 0;
    swap_count = 0;
    auto start = high_resolution_clock::now();
    
    int i, j;
    int x;
    
    for(i = 1; i < n; i++) {
        x = arr[i];
        j = i - 1;
        
        while(j >= 0) {
            comp_count++;
            if(arr[j] > x) {
                arr[j + 1] = arr[j];
                swap_count++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = x;
    }
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Execution Time (Insertion Sort): " << duration.count() << " microseconds\n";
}

// Merge Sort implementation
void merge(int h, int m, const int U[], const int V[], int S[], int &comp_count, int &swap_count) {
    int i = 1, j = 1, k = 1;
    
    while(i <= h && j <= m) {
        comp_count++;
        if(U[i-1] < V[j-1]) {
            S[k-1] = U[i-1];
            i++;
        } else {
            S[k-1] = V[j-1];
            j++;
            swap_count++;
        }
        k++;
    }
    
    if(i > h) {
        for(int x = j; x <= m; x++, k++) {
            S[k-1] = V[x-1];
        }
    } else {
        for(int x = i; x <= h; x++, k++) {
            S[k-1] = U[x-1];
        }
    }
}

void mergeSortHelper(int n, int arr[], int &comp_count, int &swap_count) {
    if(n > 1) {
        const int h = n/2;
        const int m = n - h;
        
        int* U = new int[h];
        int* V = new int[m];
        
        for(int i = 0; i < h; i++) {
            U[i] = arr[i];
        }
        
        for(int i = 0; i < m; i++) {
            V[i] = arr[h + i];
        }
        
        mergeSortHelper(h, U, comp_count, swap_count);
        mergeSortHelper(m, V, comp_count, swap_count);
        merge(h, m, U, V, arr, comp_count, swap_count);
        
        delete[] U;
        delete[] V;
    }
}

void mergeSort(int arr[], int n, int &comp_count, int &swap_count) {
    comp_count = 0;
    swap_count = 0;
    auto start = high_resolution_clock::now();
    
    mergeSortHelper(n, arr, comp_count, swap_count);
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Execution Time (Merge Sort): " << duration.count() << " microseconds\n";
}

// Quick Sort implementation
int partition(int arr[], int low, int high, int &comp_count, int &swap_count) {
    int pivotitem = arr[low];
    int j = low;
    
    for(int i = low + 1; i <= high; i++) {
        comp_count++;
        if(arr[i] < pivotitem) {
            j++;
            swap(arr[i], arr[j]);
            swap_count++;
        }
    }
    
    swap(arr[low], arr[j]);
    swap_count++;
    return j;
}

void quickSortHelper(int arr[], int low, int high, int &comp_count, int &swap_count) {
    if(high > low) {
        int pivotpoint;
        pivotpoint = partition(arr, low, high, comp_count, swap_count);
        quickSortHelper(arr, low, pivotpoint - 1, comp_count, swap_count);
        quickSortHelper(arr, pivotpoint + 1, high, comp_count, swap_count);
    }
}

void quickSort(int arr[], int n, int &comp_count, int &swap_count) {
    comp_count = 0;
    swap_count = 0;
    auto start = high_resolution_clock::now();
    
    quickSortHelper(arr, 0, n - 1, comp_count, swap_count);
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Execution Time (Quick Sort): " << duration.count() << " microseconds\n";
}

// Heap Sort implementation
struct heap {
    int* S;
    int heapsize;
};

void siftdown(heap& H, int& comp_count, int& swap_count) {
    int parent, largerchild;
    int key = H.S[0];
    
    parent = 0;
    while (2 * parent + 1 < H.heapsize) {
        comp_count++;
        if (2 * parent + 2 < H.heapsize && H.S[2 * parent + 1] < H.S[2 * parent + 2]) {
            largerchild = 2 * parent + 2;
        } else {
            largerchild = 2 * parent + 1;
        }
        
        comp_count++;
        if (key < H.S[largerchild]) {
            H.S[parent] = H.S[largerchild];
            parent = largerchild;
            swap_count++;
        } else {
            break;
        }
    }
    H.S[parent] = key;
}

int root(heap& H, int& comp_count, int& swap_count) {
    int keyout = H.S[0];
    H.S[0] = H.S[H.heapsize - 1];
    H.heapsize--;
    if (H.heapsize > 0) {
        siftdown(H, comp_count, swap_count);
    }
    return keyout;
}

void removekeys(int n, heap& H, int S[], int& comp_count, int& swap_count) {
    for (int i = n; i >= 1; i--) {
        S[i-1] = root(H, comp_count, swap_count);
    }
}

void makeheap(int n, heap& H, int& comp_count, int& swap_count) {
    int d = log2(n) + 1;
    for (int i = d - 1; i >= 0; i--) {
        int start = (int)pow(2, i) - 1;
        int end = (int)pow(2, i+1) - 1;
        for (int j = start; j < min(end, n); j++) {
            heap Hsub;
            Hsub.S = &H.S[j];
            Hsub.heapsize = min(2 * (n - j), n - j);
            siftdown(Hsub, comp_count, swap_count);
        }
    }
}

void heapSort(int arr[], int n, int& comp_count, int& swap_count) {
    comp_count = 0;
    swap_count = 0;
    auto start = high_resolution_clock::now();
    
    heap H;
    H.S = arr;
    H.heapsize = n;
    
    makeheap(n, H, comp_count, swap_count);
    removekeys(n, H, arr, comp_count, swap_count);
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Execution Time (Heap Sort): " << duration.count() << " microseconds\n";
}

// Function to test if array is sorted
bool isSorted(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        if(arr[i] > arr[i+1]) return false;
    }
    return true;
}

// Test function to run and compare all sorting algorithms
void testSortingAlgorithms(int test[], int SIZE) {
    int comp_count, swap_count;
    
    // Create arrays for each sort
    int* arr1 = new int[SIZE];
    int* arr2 = new int[SIZE];
    int* arr3 = new int[SIZE];
    int* arr4 = new int[SIZE];
    int* arr5 = new int[SIZE];
    int* arr6 = new int[SIZE];
    int* arr7 = new int[SIZE];
    
    // Copy test data to each array
    for(int i = 0; i < SIZE; i++) {
        arr1[i] = arr2[i] = arr3[i] = arr4[i] = arr5[i] = arr6[i] = arr7[i] = test[i];
    }
    
    cout << "\nSelection Sort:\n";
    selectionSort(arr1, SIZE, comp_count, swap_count);
    cout << "Comparisons: " << comp_count << ", Swaps: " << swap_count << "\n";
    cout << "Correctly sorted: " << (isSorted(arr1, SIZE) ? "Yes" : "No") << "\n\n";
    
    cout << "Exchange Sort:\n";
    exchangeSort(arr2, SIZE, comp_count, swap_count);
    cout << "Comparisons: " << comp_count << ", Swaps: " << swap_count << "\n";
    cout << "Correctly sorted: " << (isSorted(arr2, SIZE) ? "Yes" : "No") << "\n\n";
    
    cout << "Bubble Sort:\n";
    bubbleSort(arr3, SIZE, comp_count, swap_count);
    cout << "Comparisons: " << comp_count << ", Swaps: " << swap_count << "\n";
    cout << "Correctly sorted: " << (isSorted(arr3, SIZE) ? "Yes" : "No") << "\n\n";
    
    cout << "Insertion Sort:\n";
    insertionSort(arr4, SIZE, comp_count, swap_count);
    cout << "Comparisons: " << comp_count << ", Swaps: " << swap_count << "\n";
    cout << "Correctly sorted: " << (isSorted(arr4, SIZE) ? "Yes" : "No") << "\n\n";
    
    cout << "Merge Sort:\n";
    mergeSort(arr5, SIZE, comp_count, swap_count);
    cout << "Comparisons: " << comp_count << ", Swaps: " << swap_count << "\n";
    cout << "Correctly sorted: " << (isSorted(arr5, SIZE) ? "Yes" : "No") << "\n\n";
    
    cout << "Quick Sort:\n";
    quickSort(arr6, SIZE, comp_count, swap_count);
    cout << "Comparisons: " << comp_count << ", Swaps: " << swap_count << "\n";
    cout << "Correctly sorted: " << (isSorted(arr6, SIZE) ? "Yes" : "No") << "\n\n";
    
    cout << "Heap Sort:\n";
    heapSort(arr7, SIZE, comp_count, swap_count);
    cout << "Comparisons: " << comp_count << ", Swaps: " << swap_count << "\n";
    cout << "Correctly sorted: " << (isSorted(arr7, SIZE) ? "Yes" : "No") << "\n\n";
    
    // Clean up arrays
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;
}

int main() {
    const int SIZE = 1000; // Size of your test array
    int test[SIZE] = {320, 886, 92, 993, 445, 976, 429, 87, 165, 705, 598, 643, 6, 833, 911, 223, 647, 103, 544, 871, 496, 845, 838, 12, 446,
810, 644, 626, 764, 975, 892, 763, 668, 733, 561, 679, 106, 718, 881, 384, 461, 715, 448, 981, 162, 404, 7, 94, 310, 752, 732, 99, 181, 428,
597, 27, 464, 636, 684, 355, 560, 425, 375, 788, 252, 344, 215, 254, 189, 328, 682, 290, 781, 789, 813, 198, 207, 146, 790, 392, 258, 600,
547, 942, 516, 367, 491, 225, 579, 860, 926, 804, 282, 139, 922, 296, 793, 904, 624, 77, 455, 596, 823, 971, 977, 839, 859, 157, 637, 120,
321, 199, 699, 648, 564, 843, 453, 379, 465, 466, 505, 185, 535, 498, 351, 243, 71, 869, 753, 854, 33, 119, 531, 893, 741, 26, 510, 950, 812,
332, 484, 179, 237, 339, 798, 620, 154, 1000, 366, 147, 31, 17, 228, 330, 878, 378, 301, 548, 707, 877, 450, 541, 177, 386, 18, 744, 40, 232,
914, 292, 858, 916, 432, 299, 619, 640, 395, 986, 249, 760, 302, 645, 14, 941, 616, 210, 725, 173, 246, 304, 805, 818, 408, 728, 795, 100,
222, 834, 394, 946, 503, 857, 743, 32, 691, 476, 317, 711, 472, 3, 997, 137, 35, 563, 418, 49, 836, 360, 661, 778, 78, 81, 689, 963, 359, 370,
842, 108, 424, 925, 528, 454, 167, 599, 902, 338, 55, 540, 792, 8, 217, 652, 397, 41, 722, 325, 422, 241, 126, 573, 480, 349, 208, 358, 888,
796, 861, 196, 312, 870, 151, 153, 551, 513, 697, 635, 523, 915, 962, 42, 342, 952, 884, 749, 903, 724, 514, 820, 305, 152, 614, 539, 24, 784,
628, 47, 966, 615, 550, 401, 124, 811, 826, 621, 856, 336, 201, 387, 500, 474, 487, 730, 853, 416, 409, 102, 307, 758, 709, 489, 212, 116,
313, 284, 221, 747, 66, 775, 693, 69, 101, 759, 678, 768, 369, 269, 944, 729, 493, 664, 672, 537, 646, 37, 172, 587, 415, 899, 825, 291, 607,
114, 638, 86, 654, 726, 821, 586, 495, 141, 757, 895, 374, 710, 405, 190, 901, 714, 924, 274, 365, 511, 434, 440, 281, 527, 417, 674, 534,
382, 159, 255, 592, 2, 303, 133, 608, 954, 912, 935, 898, 786, 809, 270, 140, 266, 671, 75, 512, 549, 93, 110, 936, 68, 554, 931, 765, 80,
998, 874, 309, 611, 482, 97, 293, 244, 402, 323, 419, 107, 273, 276, 361, 56, 663, 184, 657, 272, 98, 420, 327, 82, 211, 203, 882, 675, 987,
138, 406, 456, 939, 734, 940, 745, 245, 239, 814, 72, 770, 623, 411, 937, 125, 216, 508, 470, 634, 802, 343, 205, 806, 777, 30, 435, 322, 388,
988, 381, 700, 145, 934, 224, 883, 891, 552, 403, 128, 447, 873, 951, 521, 350, 568, 257, 25, 90, 822, 585, 999, 306, 932, 622, 63, 584, 832,
504, 36, 978, 132, 45, 1, 533, 542, 135, 287, 740, 979, 412, 353, 59, 52, 696, 676, 991, 955, 149, 572, 785, 161, 28, 961, 475, 315, 819, 46,
717, 160, 737, 308, 569, 144, 756, 111, 701, 352, 617, 688, 220, 267, 192, 380, 444, 426, 969, 148, 967, 463, 601, 150, 721, 289, 766, 719, 5,
260, 867, 526, 326, 499, 20, 319, 670, 451, 865, 485, 960, 662, 437, 73, 187, 945, 669, 984, 529, 681, 713, 329, 783, 115, 459, 174, 39, 261,
594, 171, 575, 831, 692, 863, 195, 54, 927, 848, 277, 889, 591, 197, 155, 48, 143, 930, 655, 990, 441, 816, 773, 318, 21, 268, 690, 771, 347,
852, 314, 423, 348, 602, 735, 827, 565, 750, 685, 194, 683, 89, 16, 438, 85, 357, 800, 815, 188, 694, 285, 218, 191, 335, 164, 964, 134, 761, 769, 76, 929, 264, 994, 364, 507,
840, 543, 829, 589, 570, 202, 452, 996, 762, 943, 427, 182, 74, 88, 658, 462, 603, 706, 799, 649, 193, 439, 974, 501, 656, 471, 906, 803, 324,
577, 844, 371, 9, 230, 398, 502, 4, 43, 253, 479, 478, 410, 885, 311, 250, 995, 665, 413, 686, 19, 233, 736, 123, 553, 175, 918, 767, 209,
879, 755, 38, 251, 896, 96, 695, 469, 407, 680, 131, 235, 604, 558, 742, 231, 168, 633, 113, 875, 286, 333, 522, 949, 95, 980, 837, 612, 373,
631, 650, 70, 855, 846, 206, 368, 557, 851, 830, 213, 136, 880, 751, 473, 163, 142, 659, 262, 653, 538, 546, 519, 390, 118, 53, 376, 968, 776,
708, 121, 497, 431, 772, 156, 396, 117, 920, 84, 651, 595, 247, 278, 112, 566, 234, 817, 923, 79, 530, 436, 265, 774, 300, 559, 468, 787, 295,
567, 748, 331, 130, 876, 229, 849, 953, 956, 582, 400, 562, 62, 158, 259, 905, 109, 629, 746, 973, 393, 850, 864, 104, 723, 226, 283, 477, 11,
702, 590, 739, 556, 263, 275, 824, 630, 334, 22, 983, 83, 385, 868, 992, 57, 345, 894, 340, 716, 667, 443, 828, 67, 492, 297, 238, 703, 506,
256, 467, 15, 481, 60, 890, 791, 29, 399, 58, 509, 170, 341, 938, 958, 279, 176, 129, 605, 337, 532, 921, 957, 571, 660, 200, 363, 515, 346,
588, 712, 494, 808, 627, 51, 520, 985, 91, 807, 780, 947, 928, 65, 389, 242, 965, 910, 887, 574, 545, 44, 524, 356, 61, 430, 536, 779, 580,
458, 593, 835, 948, 214, 900, 64, 618, 186, 391, 609, 271, 578, 227, 959, 909, 576, 460, 433, 727, 517, 298, 913, 632, 34, 613, 933, 248, 383,
639, 377, 797, 754, 166, 280, 105, 698, 178, 704, 866, 731, 183, 583, 801, 518, 204, 897, 50, 907, 919, 982, 240, 989, 488, 219, 169, 555,
970, 13, 862, 581, 362, 642, 917, 294, 354, 316, 421, 236, 414, 677, 666, 525, 908, 180, 288, 372, 457, 10, 442, 490, 841, 782, 122, 483, 449,
720, 738, 606, 687, 127, 872, 610, 486, 972, 641, 23, 625, 847, 794, 673 };
    
    testSortingAlgorithms(test, SIZE);
    return 0;
}
