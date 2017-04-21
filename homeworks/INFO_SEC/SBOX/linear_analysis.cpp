#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#define getbit(src,bit) (((src)>>(bit))&0x01)


int ASbox[16 * 16] = {0x38, 0x9c, 0x46, 0x77, 0x4a, 0xd0, 0xae, 0x75, 0xed, 0x4d, 0x44, 0xcd, 0xd2, 0x11, 0xdd, 0x92,
                      0x13, 0xdf, 0x01, 0xbc, 0x17, 0x92, 0xef, 0x1d, 0xb5, 0xb2, 0xe0, 0x97, 0x9c, 0x45, 0x90, 0x8b,
                      0xf2, 0xe7, 0xfb, 0x94, 0x3b, 0x1d, 0x64, 0x76, 0x7d, 0xe7, 0x9c, 0x51, 0xa1, 0x94, 0x81, 0x1b,
                      0x1d, 0xda, 0xc5, 0x4c, 0xd0, 0x26, 0xf1, 0xdb, 0x2d, 0x31, 0xa9, 0x6a, 0x9c, 0xd4, 0x31, 0xbe,
                      0x1d, 0x1d, 0x30, 0x71, 0x2f, 0xa2, 0xb4, 0xeb, 0xf0, 0x15, 0x77, 0x8e, 0x85, 0x19, 0x61, 0x31,
                      0xbc, 0x54, 0x4d, 0xd0, 0xf0, 0xc6, 0x10, 0x81, 0x2e, 0x59, 0xb7, 0xaa, 0x95, 0xb9, 0x11, 0x72,
                      0x03, 0x65, 0x6e, 0x75, 0xee, 0x07, 0xa5, 0xbc, 0x8f, 0x01, 0x5c, 0xec, 0x46, 0x48, 0x83, 0xbd,
                      0x3a, 0x75, 0x22, 0xae, 0x40, 0x19, 0x55, 0xf8, 0xfe, 0x51, 0x94, 0xc0, 0x50, 0x9b, 0x38, 0x90,
                      0xea, 0xe8, 0x3b, 0x08, 0x3f, 0xf3, 0x40, 0xd1, 0xa2, 0xd0, 0xd3, 0xd3, 0xab, 0xc8, 0xf1, 0xa8,
                      0xdd, 0x64, 0xcb, 0x50, 0x85, 0xc8, 0xc7, 0x26, 0xe5, 0x42, 0xc8, 0x12, 0x92, 0x23, 0xaf, 0x01,
                      0x1b, 0xce, 0x22, 0x92, 0xeb, 0x0e, 0x8c, 0x12, 0x71, 0xad, 0x64, 0xab, 0x7e, 0x42, 0xb3, 0xd8,
                      0xee, 0x4a, 0xd0, 0x1c, 0x8a, 0x7a, 0x6e, 0xf4, 0x2d, 0x54, 0xd9, 0x0a, 0x26, 0xf9, 0x7d, 0xab,
                      0xde, 0x3e, 0xa8, 0x7b, 0xbb, 0x01, 0x91, 0x68, 0x43, 0xbe, 0x98, 0xdc, 0x85, 0x5d, 0xcf, 0x37,
                      0xb4, 0x4e, 0xba, 0x7c, 0x16, 0xd8, 0x53, 0x4a, 0x1c, 0xae, 0x51, 0x0f, 0xd3, 0xc4, 0xaa, 0x78,
                      0x7b, 0x60, 0x57, 0x2c, 0x74, 0x74, 0x57, 0xb9, 0x62, 0x2b, 0xf6, 0xce, 0x89, 0xc2, 0x4f, 0xac,
                      0x79, 0x99, 0x10, 0xd7, 0xf0, 0x8a, 0x7d, 0x11, 0xfc, 0x79, 0xb8, 0x88, 0x60, 0x2c, 0x3f, 0x4f
                     };

int results[16 * 16][16 * 16] = {0};

int main(int argc, char** argv)
{
    ofstream out;
    out.open("linear.csv", ios::trunc);
    for (int row = 0; row < 256; row++)
    {
        for (int col = 0; col < 256; col++)
        {
            for (int in = 0; in < 256; in++)
            {
                int sbox_ret = ASbox[in];
                int counts = 0;
                for (int index = 0; index < 8; index++)
                    counts += (int)getbit(row, index) * getbit(in, index) + (int)getbit(col, index) * getbit(sbox_ret, index);
                if (counts % 2 == 0)
                    results[row][col]++;
            }
        }
    }
    float maxs = 0.0, mins = 0.0;
    int maxrow, minrow, maxcol, mincol;
    for (int row = 0; row < 256; row++)
    {
        for (int col = 0; col < 256; col++)
        {
            out << setw(4) << results[row][col] / 256.0 - 0.5 << ',';
            if (maxs < results[row][col] / 256.0 - 0.5)
            {
                maxs = results[row][col] / 256.0 - 0.5;
                maxrow = row;
                maxcol = col;
            }
            if (mins > results[row][col] / 256.0 - 0.5)
            {
                mins = results[row][col] / 256.0 - 0.5;
                minrow = row;
                mincol = col;
            }
        }
        out << endl;
    }
    printf("max=%f,row=%d col=%d\nmin=%f,row=%d col=%d\n", maxs, maxrow, maxcol, mins, minrow, mincol);
    return 0;

}
