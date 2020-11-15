#include <iostream>
#include <string>
#include <vector>
#include <set>
#define BIT(x) (1<<(x))

using namespace std;

using uint32 = uint32_t;

void printAddress(uint32 addr);

struct Subnet {
    Subnet(const string& name, uint32 numStations) : numStations(numStations), name(name) {
        for (int i = 30; i >= 1; i--) {
            uint maxStations = BIT(i) - 2;
            if (maxStations >= numStations) {
                numBits = i;
            } else break;
        }
    }
    
    uint32 assignedAddress = 0;
    uint32 numStations;
    uint32 numBits;
    string name;

    void print() {
        printf("%s: addr = ", name.c_str());
        printAddress(assignedAddress);
        printf("/%d (mask ", 32 - numBits);
        printAddress(~(BIT(numBits) - 1));
        printf(") (%d stations)\n", numStations);
    }
    
    bool operator<(const Subnet& other) const {
        if (numStations == other.numStations) {
            return name < other.name;
        }
        return numStations > other.numStations;
    }
};

set<Subnet> subnets;

uint32 readAddress() {
    string str;
    uint32 b[4];
    int r = scanf("%u.%u.%u.%u", &b[3], &b[2], &b[1], &b[0]);
    if (r != 4) {
        return -1;
    }
    for (int i = 0; i < 4; i++) {
        if (b[i] < 0 || b[i] > 255) {
            return -1;
        }
    }
    uint32 result = 0;
    result = b[0] | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);
    return result;
}

void printAddress(uint32 addr) {
    printf("%d.%d.%d.%d", (addr >> 24) & 0xff, (addr >> 16) & 0xff, (addr >> 8) & 0xff, addr & 0xff);
}

void errorNotEnoughSpace() {
    printf("Cannot fit all subnetworks!\n");
    exit(0);
}

void errorInvalidInput() {
    printf("Please see in.txt or check Readme.md\n");
    exit(0);
}

void splitSubnet(uint32 net, uint32 netBits) {
    uint32 subnetSize = 32 - netBits;
    if (subnets.empty()) {
        return;
    }
    if (netBits == 32) {
        errorNotEnoughSpace();
    }
    auto biggestSubnet = subnets.begin();
    if (subnetSize == biggestSubnet->numBits) {
        Subnet s = *biggestSubnet;
        s.assignedAddress = net;
        s.print();
        subnets.erase(subnets.begin());
        return;
    } else if (subnetSize < biggestSubnet->numBits) {
        errorNotEnoughSpace();
    }
    splitSubnet(net, netBits + 1);
    splitSubnet(net | BIT(subnetSize - 1), netBits + 1);
}

int main()
{
    uint32 net = readAddress();
    if (net == uint32(-1)) {
        errorInvalidInput();
    }
    char name[256];
    int netMaskBits;
    int numSubnets;
    int ok = scanf("%d%d", &netMaskBits, &numSubnets);
    if (ok != 2) {
        errorInvalidInput();
    }
    for (int i = 0; i < numSubnets; i++) {
        int subnetNumStations;
        ok = scanf("%s%d", name, &subnetNumStations);
        if (ok != 2) {
            errorInvalidInput();
            exit(1);
        }
        Subnet s(name, subnetNumStations);
        subnets.insert(s);
    }
    splitSubnet(net, netMaskBits);
    if (!subnets.empty()) {
        errorNotEnoughSpace();
    }
    return 0;
}
