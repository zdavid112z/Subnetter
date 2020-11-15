# Subnetter

Given the IP address of a network and its size, split it into several
subnetworks.

## How to use:

The program takes as input the topology of the network from stdin and computes
the associated IP addresses. The following format is used:
```
A.B.C.D MaskBits
N
Subnet1_Name Subnet1_NumStations
Subnet2_Name Subnet2_NumStations
...
SubnetN_Name SubnetN_NumStations
```
Where:
- `A.B.C.D` is the base network address (i.e. 192.168.0.0)
- `MaskBits` is the number of bits in the mask (i.e. 24)
- `N` is the number of subnetworks
- `SubnetK_Name` is the name of the Kth subnetwork (i.e. Subnet1)
- `SubnetK_NumStations` is the number of stations in the Kth subnetwork (i.e. 45)


For a topology given the base address `45.67.89.0/24` which contains the following subnetworks:
- Subnetwork A with 2 routers
- Subnetwork B with 2 routers
- Subnetwork C with 45 computers
- Subnetwork D with 45 computers
- Subnetwork E with 45 computers

The input looks like this:
```
45.67.89.0 24
5
A 2
B 2
C 45
D 45
E 45
```

Use `make build` to build the app and `./subnetter` with the provided topology to run the app.

You can also use `make run`, which compiles the code, takes the input data from `in.txt` and computes the associated IP addresses.

The app is still experimental, please use it only as validation for a manually calculated solution.
