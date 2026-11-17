#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;
    double parkingFee;
public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);
    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;
    void hien_thi() const;
    void set_ma_xe(int ma);
    void set_loai_xe(string loai);
    void set_gio_vao(int gio);
    void set_tg_do(int tg);
};
phuong_tien::phuong_tien()
    : ma_xe(0), loai_xe(""), gio_vao(0),
      tg_do(0), parkingFee(0) {}
phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio),
      tg_do(tg), parkingFee(0) {
    parkingFee = tinh_phi();
}
int phuong_tien::lay_ma_xe() const {
    return ma_xe;
}
string phuong_tien::lay_loai_xe() const {
    return loai_xe;
}
void phuong_tien::set_ma_xe(int ma) {
    ma_xe = ma;
}
void phuong_tien::set_loai_xe(string loai) {
    loai_xe = loai;
    parkingFee = tinh_phi();
}
void phuong_tien::set_gio_vao(int gio) {
    gio_vao = gio;
    parkingFee = tinh_phi();
}
void phuong_tien::set_tg_do(int tg) {
    tg_do = tg;
    parkingFee = tinh_phi();
}
double phuong_tien::tinh_phi() const {
    double gia;
    if (loai_xe == "Car")
        gia = 6.0;
    else if (loai_xe == "Motorcycle")
        gia = 4.0;
    else
        gia = 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) ||
                    (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; h++) {
        if (h < 2)
            tong += gia * (cao_diem ? 1.30 : 0.95);
        else
            tong += gia * 0.90;
    }
    return tong;
}
void phuong_tien::hien_thi() const {
    cout << "  ID: " << ma_xe
         << " | " << loai_xe
         << " | " << gio_vao << "h"
         << " | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2)
         << parkingFee << "\n";
}
class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    int capacity;
    int so_xe;
    phuong_tien** ds;
public:
    bai_xe();
    bai_xe(int ma, char kt);
    ~bai_xe();
    bai_xe(const bai_xe& other);
    bai_xe& operator=(const bai_xe& other);
    int lay_ma() const;
    bool day() const;
    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    int tim_xe(int ma_xe) const;
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
    int lay_so_xe() const;
    double tong_phi() const;
};
bai_xe::bai_xe()
    : ma_bai(0), kich_thuoc('S'),
      capacity(1), so_xe(0) {
    ds = new phuong_tien*[capacity];
    for (int i = 0; i < capacity; i++)
        ds[i] = nullptr;
}
bai_xe::bai_xe(int ma, char kt)
: ma_bai(ma), kich_thuoc(kt), so_xe(0) {
    if (kt == 'S')
        capacity = 1;
    else if (kt == 'M')
        capacity = 2;
    else
        capacity = 3;
    ds = new phuong_tien*[capacity];
    for (int i = 0; i < capacity; i++)
        ds[i] = nullptr;
}
bai_xe::~bai_xe() {
    for (int i = 0; i < so_xe; i++)
        delete ds[i];
    delete[] ds;
}
bai_xe::bai_xe(const bai_xe& other) {
    ma_bai = other.ma_bai;
    kich_thuoc = other.kich_thuoc;
    capacity = other.capacity;
    so_xe = other.so_xe;
    ds = new phuong_tien*[capacity];
    for (int i = 0; i < capacity; i++)
        ds[i] = nullptr;
    for (int i = 0; i < so_xe; i++)
        ds[i] = new phuong_tien(*other.ds[i]);
}
bai_xe& bai_xe::operator=(const bai_xe& other) {
    if (this == &other)
        return *this;
    for (int i = 0; i < so_xe; i++)
        delete ds[i];
    delete[] ds;
    ma_bai = other.ma_bai;
    kich_thuoc = other.kich_thuoc;
    capacity = other.capacity;
    so_xe = other.so_xe;
    ds = new phuong_tien*[capacity];
    for (int i = 0; i < capacity; i++)
        ds[i] = nullptr;
    for (int i = 0; i < so_xe; i++)
        ds[i] = new phuong_tien(*other.ds[i]);
    return *this;
}
int bai_xe::lay_ma() const {
    return ma_bai;
}
int bai_xe::lay_so_xe() const {
    return so_xe;
}
bool bai_xe::day() const {
    return so_xe >= capacity;
}
int bai_xe::tim_xe(int ma_xe) const {
    for (int i = 0; i < so_xe; i++) {
        if (ds[i]->lay_ma_xe() == ma_xe)
            return i;
    }
    return -1;
}
bool bai_xe::chua(int ma_xe) const {
    return tim_xe(ma_xe) != -1;
}
bool bai_xe::them(phuong_tien v) {
    if (day())
        return false;
    ds[so_xe] = new phuong_tien(v);
    so_xe++;
    return true;
}
bool bai_xe::xoa(int ma_xe) {
    int vt = tim_xe(ma_xe);
    if (vt == -1)
        return false;
    delete ds[vt];
    for (int i = vt; i < so_xe - 1; i++)
        ds[i] = ds[i + 1];
    ds[so_xe - 1] = nullptr;
    so_xe--;
    return true;
}
void bai_xe::hien_thi() const {
    cout << "\nBai " << ma_bai
         << " [" << kich_thuoc << "] "
         << so_xe << "/" << capacity << " xe\n";
    if (so_xe == 0)
        cout << "Bai xe trong!\n";
    for (int i = 0; i < so_xe; i++)
        ds[i]->hien_thi();
}
bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0;
    tong = 0;
    for (int i = 0; i < so_xe; i++) {
        if (ds[i]->lay_loai_xe() == loai) {
            dem++;
            tong += ds[i]->tinh_phi();
        }
    }
    return dem > 0;
}
double bai_xe::tong_phi() const {
    double tong = 0;
    for (int i = 0; i < so_xe; i++)
        tong += ds[i]->tinh_phi();
    return tong;
}
class SystemInterface {
private:
    int lotCapacity;
    int so_bai;
    bai_xe** ds;
public:
    SystemInterface();
    ~SystemInterface();
    SystemInterface(const SystemInterface& other);
SystemInterface& operator=(const SystemInterface& other);
    void resizeSystem(int newCapacity);
    bool trung_ma_bai(int ma) const;
    bool trung_ma_xe(int ma) const;
    int generateRandomID();
    int nhap_so();
    void runMenu();
};
SystemInterface::SystemInterface()
    : lotCapacity(5), so_bai(0) {
    ds = new bai_xe*[lotCapacity];
    for (int i = 0; i < lotCapacity; i++)
        ds[i] = nullptr;
    srand(time(0));
}
SystemInterface::~SystemInterface() {
    for (int i = 0; i < so_bai; i++)
        delete ds[i];
    delete[] ds;
}
SystemInterface::SystemInterface(const SystemInterface& other) {
    lotCapacity = other.lotCapacity;
    so_bai = other.so_bai;
    ds = new bai_xe*[lotCapacity];
    for (int i = 0; i < lotCapacity; i++)
        ds[i] = nullptr;
    for (int i = 0; i < so_bai; i++)
        ds[i] = new bai_xe(*other.ds[i]);
}
SystemInterface& SystemInterface::operator=(
    const SystemInterface& other) {
    if (this == &other)
        return *this;
    for (int i = 0; i < so_bai; i++)
        delete ds[i];
    delete[] ds;
    lotCapacity = other.lotCapacity;
    so_bai = other.so_bai;
    ds = new bai_xe*[lotCapacity];
    for (int i = 0; i < lotCapacity; i++)
        ds[i] = nullptr;
    for (int i = 0; i < so_bai; i++)
        ds[i] = new bai_xe(*other.ds[i]);
    return *this;
}
void SystemInterface::resizeSystem(int newCapacity) {
    if (newCapacity <= lotCapacity)
        return;
    bai_xe** dsMoi = new bai_xe*[newCapacity];
    for (int i = 0; i < newCapacity; i++)
        dsMoi[i] = nullptr;
    for (int i = 0; i < so_bai; i++)
        dsMoi[i] = ds[i];
    delete[] ds;
    ds = dsMoi;
    lotCapacity = newCapacity;
}
bool SystemInterface::trung_ma_bai(int ma) const {
    for (int i = 0; i < so_bai; i++) {
        if (ds[i]->lay_ma() == ma)
            return true;
    }
    return false;
}
bool SystemInterface::trung_ma_xe(int ma) const {
    for (int i = 0; i < so_bai; i++) {
        if (ds[i]->chua(ma))
            return true;
    }
    return false;
}
int SystemInterface::generateRandomID() {
    int ma;
    do {
        ma = rand() % 9000 + 1000;
    } while (trung_ma_bai(ma) || trung_ma_xe(ma));
    return ma;
}
int SystemInterface::nhap_so() {
    int x;
    while (!(cin >> x)) {
        cout << "Du lieu sai! Nhap lai: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return x;
}
void SystemInterface::runMenu() {
    int chon;
    do {
        cout << "\n====================================\n";
        cout << "       QUAN LY BAI DO XE\n";
        cout << "====================================\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "====================================\n";
        cout << "Nhap lua chon: ";
        chon = nhap_so();
        switch (chon) {
        case 1: {
            int ma;
            char kt;
            cout << "Nhap kich thuoc bai (S/M/L): ";
            cin >> kt;
            if (kt >= 'a' && kt <= 'z')
                kt -= 32;
            if (kt != 'S' && kt != 'M' && kt != 'L') {
                cout << "Kich thuoc khong hop le!\n";
                break;
            }
            if (so_bai == lotCapacity)
                resizeSystem(lotCapacity * 2);
            ma = generateRandomID();
            ds[so_bai] = new bai_xe(ma, kt);
            so_bai++;
            cout << "Tao bai do thanh cong!\n";
            cout << "Ma bai: " << ma << endl;
            break;
        }
        case 2: {
            if (so_bai == 0) {
                cout << "Chua co bai do!\n";
                break;
            }
            int ma_bai;
            cout << "Nhap ma bai: ";
            ma_bai = nhap_so();
            int vt = -1;
            for (int i = 0; i < so_bai; i++) {
                if (ds[i]->lay_ma() == ma_bai) {
                    vt = i;
                    break;
                }
            }
            if (vt == -1) {
                cout << "Khong tim thay bai do!\n";
                break;
            }
            if (ds[vt]->day()) {
                cout << "Bai xe da day!\n";
                break;
            }
            int loai, gio, tg;
            cout << "Chon loai xe:\n";
            cout << "1. Car\n";
            cout << "2. Motorcycle\n";
            cout << "3. Bicycle\n";
            cout << "Nhap loai xe: ";
            loai = nhap_so();
            if (loai < 1 || loai > 3) {
                cout << "Loai xe khong hop le!\n";
                break;
            }
            string ten_loai;
            if (loai == 1)
                ten_loai = "Car";
            else if (loai == 2)
                ten_loai = "Motorcycle";
            else
                ten_loai = "Bicycle";
            cout << "Nhap gio vao (0-23): ";
            gio = nhap_so();
            if (gio < 0 || gio > 23) {
                cout << "Gio khong hop le!\n";
                break;
            }
            cout << "Nhap thoi gian do (gio): ";
            tg = nhap_so();
            if (tg <= 0) {
                cout << "Thoi gian khong hop le!\n";
                break;
            }
            int ma_xe = generateRandomID();
            phuong_tien p(ma_xe, ten_loai, gio, tg);
            if (ds[vt]->them(p)) {
                cout << "Them xe thanh cong!\n";
                cout << "Ma xe: " << ma_xe << endl;
            }
            break;
        }
        case 3: {
            int ma;
            cout << "Nhap ma bai can xoa: ";
            ma = nhap_so();
            int vt = -1;
            for (int i = 0; i < so_bai; i++) {
                if (ds[i]->lay_ma() == ma) {
                    vt = i;
                    break;
                }
            }
            if (vt == -1) {
                cout << "Khong tim thay bai do!\n";
                break;
            }
            if (ds[vt]->lay_so_xe() > 0) {
                cout << "Bai van con xe, khong the xoa!\n";
                break;
            }
            delete ds[vt];
            for (int i = vt; i < so_bai - 1; i++)
                ds[i] = ds[i + 1];
            ds[so_bai - 1] = nullptr;
            so_bai--;
            cout << "Xoa bai do thanh cong!\n";
            break;
        }
        case 4: {
            int ma;
            cout << "Nhap ma xe can lay ra: ";
            ma = nhap_so();
bool tim = false;
            for (int i = 0; i < so_bai; i++) {
                if (ds[i]->chua(ma)) {
                    ds[i]->xoa(ma);
                    cout << "Lay xe thanh cong!\n";
                    cout << "Phi gui xe: da duoc tinh theo "
                         << "thong tin luc gui.\n";
                    tim = true;
                    break;
                }
            }
            if (!tim)
                cout << "Khong tim thay xe!\n";
            break;
        }
        case 5: {
            if (so_bai == 0) {
                cout << "Chua co bai do!\n";
                break;
            }
            for (int i = 0; i < so_bai; i++)
                ds[i]->hien_thi();
            break;
        }
        case 6: {
            int ma;
            cout << "Nhap ma bai: ";
            ma = nhap_so();
            bool tim = false;
            for (int i = 0; i < so_bai; i++) {
                if (ds[i]->lay_ma() == ma) {
                    ds[i]->hien_thi();
                    tim = true;
                    break;
                }
            }
            if (!tim)
                cout << "Khong tim thay bai do!\n";
            break;
        }
        case 7: {
            int loai;
            cout << "Chon loai xe:\n";
            cout << "1. Car\n";
            cout << "2. Motorcycle\n";
            cout << "3. Bicycle\n";
            cout << "Nhap lua chon: ";
            loai = nhap_so();
            if (loai < 1 || loai > 3) {
                cout << "Loai xe khong hop le!\n";
                break;
            }
            string ten_loai;
            if (loai == 1)
                ten_loai = "Car";
            else if (loai == 2)
                ten_loai = "Motorcycle";
            else
                ten_loai = "Bicycle";
            int dem = 0;
            double tong = 0;
            cout << "\nDanh sach xe " << ten_loai << ":\n";
            for (int i = 0; i < so_bai; i++) {
                int d = 0;
                double t = 0;
                if (ds[i]->co_loai(ten_loai, d, t)) {
                    ds[i]->hien_thi();
                    dem += d;
                    tong += t;
                }
            }
            if (dem == 0) {
                cout << "Khong co xe loai nay!\n";
            } else {
                cout << "Tong so xe: " << dem << endl;
                cout << "Tong phi: $" << fixed
                     << setprecision(2) << tong << endl;
            }
            break;
        }
        case 8: {
            int dem = 0;
            double tong = 0;
            for (int i = 0; i < so_bai; i++) {
                dem += ds[i]->lay_so_xe();
                tong += ds[i]->tong_phi();
            }
cout << "\n===== BAO CAO PHI =====\n";
            cout << "Tong so bai: " << so_bai << endl;
            cout << "Tong so xe: " << dem << endl;
            cout << "Tong phi: $" << fixed
                 << setprecision(2) << tong << endl;
            if (dem > 0) {
                cout << "Phi trung binh: $"
                     << fixed << setprecision(2)
                     << tong / dem << endl;
            } else {
                cout << "Chua co xe de tinh trung binh!\n";
            }
            break;
        }
        case 9:
            cout << "Thoat chuong trinh!\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (chon != 9);
}
int main() {
    SystemInterface ql;
    ql.runMenu();
    return 0;
}
