from sorting_algorithms.algorithms.generic_sort import GenericSort


class SelectionSort(GenericSort):
    def __init__(self, iterable, key, reverse, cmp) -> None:
        super().__init__(iterable, key, reverse, cmp)

    def sort(self) -> None:
        for i in range(len(self.iterable) - 1):
            for j in range(i + 1, len(self.iterable)):
                if not self._in_order(self.iterable[i], self.iterable[j]):
                    self.iterable[i], self.iterable[j] = (
                        self.iterable[j],
                        self.iterable[i],
                    )
