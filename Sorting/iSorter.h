// Sorter Interface
// iSorter.h

class iSorter {
public:
    virtual ~iSorter() = default;
    virtual void sort(float*, int) = 0;
    virtual const char* name() const = 0;
};

iSorter* CreateSorter(int);
int noOfSorters();