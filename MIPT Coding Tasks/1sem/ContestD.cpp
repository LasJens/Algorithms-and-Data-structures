#include <iostream>

struct Taxi{
  int num = 0;
  int tax = 0;
};

struct Person{
  int num = 0;
  int dist = 0;
};

struct Match{
  int per = 0;
  int txi = 0;
};

void TaxiMerge(Taxi* array, int left, int middle, int right) {
  Taxi merged_array[1001];
  int i_left = left;
  int i_right = middle + 1;
  int i_merged_array = 0;
  while (i_left <= middle and i_right <= right) {
    if (array[i_left].tax <= array[i_right].tax) {
      merged_array[i_merged_array].tax = array[i_left].tax;
      merged_array[i_merged_array].num = array[i_left].num;
      i_merged_array++;
      i_left++;
    } else {
      merged_array[i_merged_array].tax = array[i_right].tax;
      merged_array[i_merged_array].num = array[i_right].num;
      i_merged_array++;
      i_right++;
    }
  }
  while (i_left <= middle) {
    merged_array[i_merged_array].tax = array[i_left].tax;
    merged_array[i_merged_array].num = array[i_left].num;
    i_merged_array++;
    i_left++;
  }
  while (i_right <= right) {
    merged_array[i_merged_array].tax = array[i_right].tax;
    merged_array[i_merged_array].num = array[i_right].num;
    i_merged_array++;
    i_right++;
  }
  for (int i = left; i <= right; ++i) {
    array[i].tax = merged_array[i - left].tax;
    array[i].num = merged_array[i - left].num;
  }
}

void TaxiMergeSort(Taxi* array, int left, int right) {
  if (left >= right) {
  } else {
    int middle = (left + right) / 2;
    TaxiMergeSort(array, left, middle);
    TaxiMergeSort(array, middle + 1, right);
    TaxiMerge(array, left, middle, right);
  }
}

void PersMerge(Person* array, int left, int middle, int right) {
  Person merged_array[1001];
  int i_left = left;
  int i_right = middle + 1;
  int i_merged_array = 0;
  while (i_left <= middle and i_right <= right) {
    if (array[i_left].dist <= array[i_right].dist) {
      merged_array[i_merged_array].dist = array[i_left].dist;
      merged_array[i_merged_array].num = array[i_left].num;
      i_merged_array++;
      i_left++;
    } else {
      merged_array[i_merged_array].dist = array[i_right].dist;
      merged_array[i_merged_array].num = array[i_right].num;
      i_merged_array++;
      i_right++;
    }
  }
  while (i_left <= middle) {
    merged_array[i_merged_array].dist = array[i_left].dist;
    merged_array[i_merged_array].num = array[i_left].num;
    i_merged_array++;
    i_left++;
  }
  while (i_right <= right) {
    merged_array[i_merged_array].dist = array[i_right].dist;
    merged_array[i_merged_array].num = array[i_right].num;
    i_merged_array++;
    i_right++;
  }
  for (int i = left; i <= right; ++i) {
    array[i].dist = merged_array[i - left].dist;
    array[i].num = merged_array[i - left].num;
  }
}

void PersMergeSort(Person* array, int left, int right) {
  if (left >= right) {
  } else {
    int middle = (left + right) / 2;
    PersMergeSort(array, left, middle);
    PersMergeSort(array, middle + 1, right);
    PersMerge(array, left, middle, right);
  }
}

void MatchMerge(Match* array, int left, int middle, int right) {
  Match merged_array[1001];
  int i_left = left;
  int i_right = middle + 1;
  int i_merged_array = 0;
  while (i_left <= middle and i_right <= right) {
    if (array[i_left].per <= array[i_right].per) {
      merged_array[i_merged_array].per = array[i_left].per;
      merged_array[i_merged_array].txi = array[i_left].txi;
      i_merged_array++;
      i_left++;
    } else {
      merged_array[i_merged_array].per = array[i_right].per;
      merged_array[i_merged_array].txi = array[i_right].txi;
      i_merged_array++;
      i_right++;
    }
  }
  while (i_left <= middle) {
    merged_array[i_merged_array].per = array[i_left].per;
    merged_array[i_merged_array].txi = array[i_left].txi;
    i_merged_array++;
    i_left++;
  }
  while (i_right <= right) {
    merged_array[i_merged_array].per = array[i_right].per;
    merged_array[i_merged_array].txi = array[i_right].txi;
    i_merged_array++;
    i_right++;
  }
  for (int i = left; i <= right; ++i) {
    array[i].per = merged_array[i - left].per;
    array[i].txi = merged_array[i - left].txi;
  }
}

void MatchMergeSort(Match* array, int left, int right) {
  if (left >= right) {
  } else {
    int middle = (left + right) / 2;
    MatchMergeSort(array, left, middle);
    MatchMergeSort(array, middle + 1, right);
    MatchMerge(array, left, middle, right);
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  auto pers = new Person[n];
  auto txis = new Taxi[n];
  auto match = new Match[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> pers[i].dist;
    pers[i].num = i + 1;
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> txis[i].tax;
    txis[i].num = i + 1;
  }
  PersMergeSort(pers, 0, n - 1);
  TaxiMergeSort(txis, 0, n - 1);
  for (int i = 0; i < n; ++i) {
    match[i].per = pers[i].num;
    match[i].txi = txis[n - 1 - i].num;
  }
  MatchMergeSort(match, 0, n - 1);
  for (int i = 0; i < n; ++i) {
    std::cout << match[i].txi << " ";
  }
  delete[] pers;
  delete[] txis;
  delete[] match;
}