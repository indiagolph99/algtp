// В супермаркете решили оптимизировать показ рекламы. Известно расписание
// прихода и ухода покупателей (два целых числа). Каждому покупателю необходимо
// показать минимум 2 рекламы. Рекламу можно транслировать только в целочисленные
// моменты времени. Покупатель может видеть рекламу от момента прихода до момента
// ухода из магазина. В каждый момент времени может показываться только одна
// реклама. Считается, что реклама показывается мгновенно. Если реклама показывается
// в момент ухода или прихода, то считается, что посетитель успел её посмотреть.
// Требуется определить минимальное число показов рекламы.

#include <iostream>
#include <string>
// pair represents begin and end of visitor presence respectively
struct pair {
    int first;
    int second;
};
// arrange period by its beginning, if ends are equal
void insert(struct pair *arr, int index) {
    int t = index;
    while (arr[t].second == arr[t - 1].second && arr[t - 1].first > arr[t].first) {
        struct pair temp = arr[t];
        arr[t] = arr[t - 1];
        arr[t - 1] = temp;
        --t;
    }
}

//merge by the end of time period in ascending order
void merge(int left, int right, int mid, struct pair* arr) {
    int it_left = mid - left + 1;
    int it_right = right - mid;
    size_t i, j, k;
    struct pair left_arr[it_left];
    struct pair right_arr[it_right];

    for (i = 0; i < it_left; i++) {
        left_arr[i] = arr[left + i];
    }

    for (j = 0; j < it_right; j++) {
        right_arr[j] = arr[mid + j + 1];
    }
    i = 0;
    j = 0;
    k = left;
    int t = 0;
    while (i < it_left && j < it_right) {
        if (left_arr[i].second <= right_arr[j].second) {
            arr[k] = left_arr[i];
            insert(arr, k);
            i++;
        } else {
            arr[k] = right_arr[j];
            insert(arr, k);
            j++;
        }
        k++;
    }

    while (i < it_left) {
        arr[k] = left_arr[i];
        insert(arr, k);
        i++;
        k++;
    }

    while (j < it_right) {
        arr[k] = right_arr[j];
        insert(arr,k);
        j++;
        k++;
    }
}

void merge_sort(int left, int right, struct pair* arr) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(left, mid, arr);
        merge_sort(mid + 1, right, arr);
        merge(left, right, mid, arr);
    }
}

int count_bans(struct pair* arr, int n) {
    // two optimal show-times are chosen:
    // end and before end
    int ban_two = arr[0].second;
    int ban_one = ban_two - 1;
    int count = 2;
    for (size_t i = 1; i < n; i++) {
        // if one period ends before next begins - they have no intersection points
        if (ban_two < arr[i].first) {
            ban_two = arr[i].second;
            ban_one = ban_two - 1;
            count += 2;
        }
        // exactly one intersection - another banner is required
        if (ban_two == arr[i].first) {
            ban_one = ban_two;
            ban_two = arr[i].second;
            ++count;
        }
  
        if (ban_two > arr[i].first) {
            if (ban_one < arr[i].first) {
                ban_one = ban_two;
                ban_two = arr[i].second;
                count++;
            }
        }
    }
    return count;
}


int main() {
    int n = 0;
    int count = 0;
    struct pair* arr = nullptr;
    std::cin >> n;
    arr = new struct pair[n];
    for (size_t i = 0; i < n; i++) {
        std::cin >> arr[i].first >> arr[i].second;
    }

    merge_sort(0, n - 1, arr);
    count = count_bans(arr, n);
    std::cout << count << '\n';
    return 0;
}
