#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Forward declarations for Order and Product classes
class Order;
class Product;

class Employee {
private:
    string employeeID;
    string name;
    string position;
    double salary;
    int workingHours;

public:
    // Constructor
    Employee(string id = "", string n = "", string pos = "", double sal = 0.0, int hours = 0)
        : employeeID(id), name(n), position(pos), salary(sal), workingHours(hours) {
    }
    
    //// Các phương thức xử lý công việc
    //void processOrder(Order order) {
    //    // Implementation would depend on Order class
    //}

    //void updateStock(Product product, int quantity) {
    //    // Implementation would depend on Product class
    //}
    
    // Phương thức hiển thị tiêu đề (static)
    static void displayHeader() {
        cout << left
            << setw(8) << "Ma NV"
            << setw(20) << "Ten"
            << setw(15) << "Chuc vu"
            << right
            << setw(12) << "Luong"
            << setw(10) << "Gio lam"
            << endl;

        cout << setfill('-');
        cout << setw(7) << "" << " "
            << setw(19) << "" << " "
            << setw(14) << "" << " "
            << setw(12) << "" << " "
            << setw(10) << "" << endl;
        cout << setfill(' '); // Reset fill character
    }

    // Phương thức hiển thị hàng dữ liệu
    void displayRow() const {
        cout << left
            << setw(8) << employeeID
            << setw(20) << name
            << setw(15) << position
            << right
            << setw(12) << fixed << setprecision(0) << salary
            << setw(10) << workingHours
            << endl;
    }

    // Getters
    string getID() const { return employeeID; }
    string getName() const { return name; }
    string getPosition() const { return position; }
    double getSalary() const { return salary; }
    int getWorkingHours() const { return workingHours; }

    // Setters
    void setSalary(double newSalary) { salary = newSalary; }
    void setPosition(const string& newPos) { position = newPos; }
    void setWorkingHours(int hours) { workingHours = hours; }

    void AddEmployee()
    {
        Employee nv;
        int maNhanVienSo;
        string chucVuNhap;

        // Nhập mã nhân viên
        while (true) {
            cout << "Nhap ma nhan vien (toi da 3 so): ";
            cin >> maNhanVienSo;
            if (maNhanVienSo >= 1 && maNhanVienSo <= 999) {
                break;
            }
            else {
                cout << "Ma nhan vien khong hop le. Vui long nhap lai." << endl;
            }
        }

        // Nhập họ tên
        cout << "Nhap ho ten (toi da 35 ky tu): ";
        cin.ignore();
        getline(cin, nv.name);
        while (nv.name.length() > 35) {
            cout << "Ho ten qua dai. Vui long nhap lai: ";
            getline(cin, nv.name);
        }

        // Nhập chức vụ
        while (true) {
            cout << "Nhap chuc vu (NV hoac QL): ";
            cin >> chucVuNhap;
            if (chucVuNhap == "NV" || chucVuNhap == "QL") {
                break;
            }
            else {
                cout << "Chuc vu khong hop le. Vui long nhap lai." << endl;
            }
        }

        // Nhập lương
        while (true) {
            cout << "Nhap luong (toi da 20,000,000 va khong am): ";
            cin >> nv.salary;
            if (nv.salary >= 0 && nv.salary <= 20000000) {
                break;
            }
            else {
                cout << "Luong khong hop le. Vui long nhap lai." << endl;
            }
        }

        // Nhập số giờ làm
        while (true) {
            cout << "Nhap so gio lam (toi da 12): ";
            cin >> nv.workingHours;
            if (nv.workingHours >= 0 && nv.workingHours <= 12) {
                break;
            }
            else {
                cout << "So gio lam khong hop le. Vui long nhap lai." << endl;
            }
        }

        // Định dạng mã nhân viên
        stringstream ss;
        ss << setw(3) << setfill('0') << maNhanVienSo;
        string maNhanVienFormatted = ss.str();

        // Thêm tiền tố vào mã nhân viên dựa trên chức vụ
        if (chucVuNhap == "NV") {
            nv.employeeID = "NV" + maNhanVienFormatted;
            nv.position = "Nhan vien";
        }
        else {
            nv.employeeID = "QL" + maNhanVienFormatted;
            nv.position = "Quan ly";
        }
        
    }


};

class EmployeeManager
{
private:
    vector<Employee> ds_nhanvien;
public:
    void ReadFromFile() {
        string filename = "Employees.csv";
        ifstream file(filename);

        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, name, pos, salStr, hoursStr;

            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, pos, ',');
            getline(ss, salStr, ',');
            getline(ss, hoursStr);

            try {
                double salary = stod(salStr);
                int hours = stoi(hoursStr);
                ds_nhanvien.emplace_back(id, name, pos, salary, hours);
            }
            catch (const exception& e) {
                cerr << "Error parsing data: " << e.what() << endl;
            }
        }

        file.close();
    }

    void WriteToFile() {
        string filename = "Employees.csv";
        ofstream file(filename);

        if (!file.is_open()) {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        for (const auto& emp : ds_nhanvien) {
            file << emp.getID() << ","
                << emp.getName() << ","
                << emp.getPosition() << ","
                << fixed << setprecision(0) << emp.getSalary() << ","
                << emp.getWorkingHours() << "\n";
        }

        file.close();
    }

    void displayInfor_ALL()
    {
        Employee::displayHeader();
        for (const auto& emp : ds_nhanvien)
        {
            emp.displayRow();
        }
    }

    void InputEmployeeData(string &employeeID,string &name, string &position, double &salary,int &workingHours)
    {
        int maNhanVienSo;
        string chucVuNhap;
        // Nhập mã nhân viên
        while (true) {
            cout << "Nhap ma nhan vien (toi da 3 so): ";
            cin >> maNhanVienSo;
            if (cin.fail())  // Trả về giá trị true nếu lần nhập trước thất bại
            {
                cin.clear(); // Xoá cờ lỗi
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Loại bỏ dữ liệu lỗi
                cout << "Ma nhan vien khong hop le. Vui long nhap lai." << endl;
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if ((maNhanVienSo) >= 1 && (maNhanVienSo) <= 999) {
                    break;
                }
                else {
                    cout << "Ma nhan vien khong hop le. Vui long nhap lai." << endl;
                }
            }
            
        }

        // Nhập họ tên
        cout << "Nhap ho ten (toi da 35 ky tu): ";
        cin.ignore();
        getline(cin, name);
        while (name.length() > 35) {
            cout << "Ho ten qua dai. Vui long nhap lai: ";
            getline(cin, name);
        }

        // Nhập chức vụ
        while (true) {
            cout << "Nhap chuc vu (NV hoac QL): ";
            cin >> chucVuNhap;
            if (chucVuNhap == "NV" || chucVuNhap == "QL") {
                break;
            }
            else {
                cout << "Chuc vu khong hop le. Vui long nhap lai." << endl;
            }
        }

        // Nhập lương
        while (true) {
            cout << "Nhap luong (toi da 20,000,000 va khong am): ";
            cin >> salary;
            if (salary >= 0 && salary <= 20000000) {
                break;
            }
            else {
                cout << "Luong khong hop le. Vui long nhap lai." << endl;
            }
        }

        // Nhập số giờ làm
        while (true) {
            cout << "Nhap so gio lam (toi da 12): ";
            cin >> workingHours;
            if (workingHours >= 0 && workingHours <= 12) {
                break;
            }
            else {
                cout << "So gio lam khong hop le. Vui long nhap lai." << endl;
            }
        }

        // Định dạng mã nhân viên
        stringstream ss;
        ss << setw(3) << setfill('0') << maNhanVienSo;
        string maNhanVienFormatted = ss.str();

        // Thêm tiền tố vào mã nhân viên dựa trên chức vụ
        if (chucVuNhap == "NV") {
            employeeID = "NV" + maNhanVienFormatted;
            position = "Nhan vien";
        }
        else {
            employeeID = "QL" + maNhanVienFormatted;
            position = "Quan ly";
        }
    }

    void AddEmployee() {
        string employeeID;
        string name;
        string position;
        double salary;
        int workingHours;

        ds_nhanvien:InputEmployeeData(employeeID, name, position, salary, workingHours);
        
        ds_nhanvien.emplace_back(employeeID, name, position, salary, workingHours);
    }

    void EditEmployee() {

    }

};

// Example usage
int main() {
    EmployeeManager qly;
    qly.ReadFromFile();
    qly.displayInfor_ALL();

    qly.AddEmployee();
    cout << "==================Danh sach sau khi nhap:\n";
    qly.displayInfor_ALL();

    qly.WriteToFile();

    return 0;
}
