
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>
#include <algorithm>

using namespace std;

// Forward declarations for Order and Product classes
class Order;
class Product;

class Employee {
private:
    string employeeID;
    string name;
    string position;
    string salary;
    int workingHours;

public:
    // Constructor
    Employee(string id = "", string n = "", string pos = "", string sal = "", int hours = 0)
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
            << setw(12) << salary
            << setw(10) << workingHours
            << endl;
    }

    // Phương thức kiểm tra thông tin nhập vào (empty = false là dữ liệu không được trống, true là được)
    bool checkInputID(string ID, bool empty = false)
    {
        if (ID.empty() and !empty) // Kiểm tra xem có bỏ trống không
        {
            cout << "Ma nhan vien khong duoc de trong. Vui long nhap lai." << endl;
            return false;
        }
        if (ID.empty() and empty) return true;
        for (char c : ID) // Kiểm tra xem có phải số không
        {
            if (isalpha(c))
            {
                cout << "Ma nhan vien khong chua ky tu. Vui long nhap lai." << endl;
                return false;
            }
        }
        if (stoi(ID) >= 1 && stoi(ID) <= 999) // Kiểm tra xem có trong khoảng không
        {
            return true;
        }
        else
        {
            cout << "Ma nhan vien chi tu (1 -> 999). Vui long nhap lai." << endl;
            return false;
        }
    }
    bool checkInputName(string name, bool empty = false)
    {
        if (name.empty() and !empty) // Kiểm tra xem có bỏ trống không
        {
            cout << "Ho ten khong duoc de trong. Vui long nhap lai." << endl;
            return false;
        }
        if (name.empty() and empty) return true;
        for (char c : name) // Kiểm tra xem có phải chữ không
        {
            if (isdigit(c))
            {
                cout << "Ten khong chua so. Vui long nhap lai." << endl;
                return false;
            }
        }
        if (name.length() > 20)
        {
            cout << "Ho ten qua dai. Vui long nhap lai." << endl;
            return false;
        }
        return true;
    }
    bool checkInputPosition(string pos, bool empty = false)
    {
        if (pos.empty() and !empty) // Kiểm tra xem có bỏ trống không
        {
            cout << "Chuc vu khong duoc de trong. Vui long nhap lai." << endl;
            return false;
        }
        if (pos.empty() and empty) return true;
        if (pos == "NV" || pos == "QL")
            return true;
        else
        {
            cout << "Chuc vu khong hop le. Vui long nhap lai." << endl;
            return false;
        }
    }
    bool checkInputSalary(string& salary, bool empty = false)
    {
        if (salary.empty() and !empty) // Kiểm tra xem có bỏ trống không
        {
            cout << "Luong khong duoc de trong. Vui long nhap lai." << endl;
            return false;
        }
        if (salary.empty() and empty) return true; // Kiểm tra xem có bỏ trống không
        for (char c : salary) // Kiểm tra xem có phải số không
        {
            if (isalpha(c))
            {
                cout << "Luong khong chua ky tu. Vui long nhap lai." << endl;
                return false;
            }
        }
        removeSpace(salary); // Xóa khoảng trắng
        if (stod(salary) >= 0 && stod(salary) <= 20000000) // Kiểm tra xem có trong khoảng không
        {
            return true;
        }
        else
        {
            cout << "Luong chi tu (0 -> 20,000,000). Vui long nhap lai." << endl;
            return false;
        }
    }
    bool checkInputWorkingHours(string workingHours, bool empty = false)
    {
        if (workingHours.empty() and !empty) // Kiểm tra xem có bỏ trống không
        {
            cout << "So gio lam khong duoc de trong. Vui long nhap lai." << endl;
            return false;
        }
        if (workingHours.empty() and empty) return true; // Kiểm tra xem có bỏ trống không
        for (char c : workingHours) // Kiểm tra xem có phải số không
        {
            if (isalpha(c))
            {
                cout << "So gio lam khong chua ky tu. Vui long nhap lai." << endl;
                return false;
            }
        }
        if (stoi(workingHours) >= 0 && stoi(workingHours) <= 12) // Kiểm tra xem có trong khoảng không
        {
            return true;
        }
        else
        {
            cout << "So gio lam chi tu (0 -> 12). Vui long nhap lai." << endl;
            return false;
        }
    }

    // Phương thức cập nhật thông tin
    void editID(bool empty = false) {
        bool check = false;
        string ID_temp;
        while (!check)
        {
            cout << "Nhap ma nhan vien (toi da 3 so): ";
            getline(cin, ID_temp);
            check = checkInputID(ID_temp, empty);
        }
        if (!ID_temp.empty()) setID(ID_temp); // Nếu không trống thì lưu
    }
    void editName(bool empty = false) {
        bool check = false;
        string name_temp;
        while (!check)
        {
            cout << "Nhap ho ten (toi da 20 ky tu): ";
            getline(cin, name_temp);
            check = checkInputName(name_temp, empty);
        }
        if (!name_temp.empty()) setName(name_temp);
    }
    void editPos(bool empty = false) {
        bool check = false;
        string pos_temp;
        while (!check)
        {
            cout << "Nhap chuc vu (NV hoac QL): ";
            getline(cin, pos_temp);
            check = checkInputPosition(pos_temp, empty);
        }
        if (!pos_temp.empty()) setPosition(pos_temp);
    }
    void editSalary(bool empty = false) {
        bool check = false;
        string sal_temp;
        while (!check)
        {
            cout << "Nhap luong (toi da 20,000,000): ";
            getline(cin, sal_temp);
            check = checkInputSalary(sal_temp, empty);
        }
        if (!sal_temp.empty()) setSalary(sal_temp);
    }
    void editWHours(bool empty = false) {
        bool check = false;
        string wh_temp;
        while (!check)
        {
            cout << "Nhap so gio lam (toi da 12): ";
            getline(cin, wh_temp);
            check = checkInputWorkingHours(wh_temp, empty);
        }
        if (!wh_temp.empty()) setWorkingHours(stoi(wh_temp));
    }

    // Xử lý dữ liệu lương
    void removeSpace(string& salary)
    {
        salary.erase(remove(salary.begin(), salary.end(), ' '), salary.end());
    }

    void fomatSalary(string& salary)
    {
        string result;
        int count = 0;
        for (int i = salary.length() - 1; i >= 0; --i) {
            result = salary[i] + result;
            count++;
            if (count % 3 == 0 && i != 0) {
                result = " " + result;
            }
        }
        salary = result;
    }

    // Getters
    string getID() const { return employeeID; }
    string getName() const { return name; }
    string getPosition() const { return position; }
    string getSalary() const { return salary; }
    int getWorkingHours() const { return workingHours; }

    // Setters
    void setID(const string& newID)
    {
        // Định dạng mã nhân viên
        stringstream ss;
        ss << setw(3) << setfill('0') << newID;
        string ID_Formatted = ss.str();
        employeeID = ID_Formatted;
    }
    void setName(const string& newName) { name = newName; }
    void setSalary(string newSalary)
    {
        fomatSalary(newSalary);
        salary = newSalary;
    }
    void setPosition(const string& newPos)
    {
        // Định dạng lại chức vụ
        if (newPos == "NV") {
            position = "Nhan vien";
        }
        else {
            position = "Quan ly";
        }
    }
    void setWorkingHours(int hours) { workingHours = hours; }

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

        bool isFirstLine = true; // Thêm biến boolean để kiểm tra dòng đầu tiên

        string line;
        while (getline(file, line)) {
            if (isFirstLine) {
                isFirstLine = false;
                continue; // Bỏ qua dòng đầu tiên
            }
            stringstream ss(line);
            string id, name, pos, sal, hoursStr;

            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, pos, ',');
            getline(ss, sal, ',');
            getline(ss, hoursStr);

            try {
                int hours = stoi(hoursStr);
                ds_nhanvien.emplace_back(id, name, pos, sal, hours);
            }
            catch (const exception& e) {
                cerr << "Error parsing data: " << e.what() << endl;
            }
        }

        SortByID();

        file.close();
    }

    void WriteToFile() {
        string filename = "Employees.csv";
        ofstream file(filename);

        if (!file.is_open()) {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        SortByID();
        file << "Ma NV,Ten,Chuc vu,Luong,Gio lam\n";

        for (const auto& emp : ds_nhanvien) {
            file << emp.getID() << ","
                << emp.getName() << ","
                << emp.getPosition() << ","
                << emp.getSalary() << ","
                << emp.getWorkingHours() << "\n";
        }

        file.close();
    }

    void SortByID()
    {
        if (ds_nhanvien.size() > 1)
        {
            sort(ds_nhanvien.begin(), ds_nhanvien.end(), [](const Employee& emp1, const Employee& emp2)
                {
                    return stoi(emp1.getID()) < stoi(emp2.getID());
                });
        }
    }

    void displayInfor_ALL()
    {
        cout << "============ Danh sach nhan vien ============" << endl;
        Employee::displayHeader();
        for (const auto& emp : ds_nhanvien)
        {
            emp.displayRow();
        }
    }

    bool checkDuplicateID(const int ID)
    {
        for (const auto& emp : ds_nhanvien)
        {
            if (stoi(emp.getID()) == ID)
            {
                cout << "Ma nhan vien da ton tai. Vui long nhap lai." << endl;
                return true;
            }
        }
        return false;
    }

    void AddEmployee() {
        Employee emp;

        // Nhập ID nhân viên
        while (true)
        {
            emp.editID();
            if (!checkDuplicateID(stoi(emp.getID())))
            {
                break;
            }
        }

        // Nhập tên nhân viên
        emp.editName();

        // Nhập chức vụ
        emp.editPos();

        // Nhập lương
        emp.editSalary();

        // Nhập số giờ làm
        emp.editWHours();

        ds_nhanvien.emplace_back(emp);

        cout << "Nhap thanh cong nhan vien:\n";
        Employee::displayHeader();
        emp.displayRow();

        WriteToFile();
    }

    int SreachIndexEmployeeByID(const string ID_so)
    {
        // Định dạng mã nhân viên
        stringstream ss;
        ss << setw(3) << setfill('0') << ID_so;
        string ID_Formatted = ss.str();
        for (int i = 0; i < ds_nhanvien.size(); i++)
        {
            if (ds_nhanvien[i].getID() == ID_Formatted)
                return i;
        }
        return -1;
    }

    void EditEmployee() {
        string ID_sreach;
        cout << "Nhap ma nhan vien can sua: ";
        getline(cin, ID_sreach);

        // Tìm kiếm nhân viên trong danh sách
        int viTri = SreachIndexEmployeeByID(ID_sreach);
        if (viTri == -1) {
            cout << "Khong tim thay nhan vien co ma " << ID_sreach << endl;
            return;
        }

        // Hiển thị thông tin hiện tại
        cout << "Thong tin nhan vien hien tai:" << endl;
        Employee::displayHeader();
        ds_nhanvien[viTri].displayRow();
        cout << endl;

        // Cho phép sửa thông tin
        cout << "Nhap thong tin moi (nhan Enter de giu nguyen):" << endl;

        // Sửa thông tin nhân viên
        // Nhập ID nhân viên
        int ID_Old = stoi(ds_nhanvien[viTri].getID()); // Lấy ID cũ chưa cập nhật
        while (true)
        {
            ds_nhanvien[viTri].editID(true);
            if (stoi(ds_nhanvien[viTri].getID()) == ID_Old) // Kiểm tra ID có thay đổi hay không
                break;
            if (!checkDuplicateID(stoi(ds_nhanvien[viTri].getID()))) // Kiểm tra xem có trùng với ID khác không
                break;
        }

        // Nhập tên nhân viên
        ds_nhanvien[viTri].editName(true);

        // Nhập chức vụ
        ds_nhanvien[viTri].editPos(true);

        // Nhập lương
        ds_nhanvien[viTri].editSalary(true);

        // Nhập số giờ làm
        ds_nhanvien[viTri].editWHours(true);

        cout << "\nSua thong tin nhan vien thanh cong thanh:\n";
        Employee::displayHeader();
        ds_nhanvien[viTri].displayRow();

        cout << "Sua thong tin nhan vien thanh cong!" << endl;
        WriteToFile();
    }

    void SreachEmployeeByID()
    {
        string ID_sreach;
        cout << "Nhap ma nhan vien can tim (nhap so) : ";
        cin >> ID_sreach;
        cin.ignore();
        // Tìm kiếm nhân viên trong danh sách
        int viTri = SreachIndexEmployeeByID(ID_sreach);
        if (viTri == -1) {
            cout << "Khong tim thay nhan vien co ma " << ID_sreach << endl;
            return;
        }
        // Hiển thị thông tin hiện tại
        cout << "Thong tin nhan vien can tim la:" << endl;
        Employee::displayHeader();
        ds_nhanvien[viTri].displayRow();
    }

    void RemoveEmployeeByID()
    {
        string ID_sreach;
        cout << "Nhap ma nhan vien can xoa (nhap so): ";
        cin >> ID_sreach;
        cin.ignore();
        // Tìm kiếm nhân viên trong danh sách
        int viTri = SreachIndexEmployeeByID(ID_sreach);
        if (viTri == -1) {
            cout << "Khong tim thay nhan vien co ma " << ID_sreach << endl;
            return;
        }
        else {
            // Hiển thị nhân viên chuẩn bị xóa
            cout << "Thong tin nhan vien muon xoa" << endl;
            Employee::displayHeader();
            ds_nhanvien[viTri].displayRow();
            cout << endl;
            string confirm;
            while (true)
            {
                cout << "Xac nhan (Y/N): ";
                getline(cin, confirm);
                if (confirm == "Y" or confirm == "N")
                    break;
                cout << "Du lieu nhap khong hop le. Vui long nhap lai. " << endl;
            }
            if (confirm == "Y") // nếu confirm bằng Y thì xóa và cập nhật vào file
            {
                ds_nhanvien.erase(ds_nhanvien.begin() + viTri);
                WriteToFile();
                cout << "Xoa thanh cong nhan vien" << endl;
            }
            else
            {
                cout << "Huy lenh xoa nhan vien." << endl;
                return;
            }
        }
    }
};

static void menu_QL_NhanVien()
{
    EmployeeManager ql;
    int chon = 0;
    ql.ReadFromFile();
    while (chon != 8)
    {
        system("cls");
        cout << "============ Quan ly nhan vien ============\n"
            << "1. Them nhan vien\n"
            << "2. Cap nhat thong tin nhan vien\n"
            << "3. Hien thi danh sach nhan vien\n"
            << "4. Tim nhan vien theo ID\n"
            << "5. Xoa nhan vien theo ID\n"
            << "6. Chua co\n"
            << "7. Chua co\n"
            << "8. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> chon;
        cin.ignore();

        if (cin.fail())  // Trả về giá trị true nếu lần nhập trước thất bại
        {
            cin.clear(); // Xoá cờ lỗi
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Loại bỏ dữ liệu lỗi
            cout << "Lua chon khong hop le. Vui long nhap lai!\n";
            cout << "\nAN Enter de quay lai man hinh chon....";
            cin.get();
        }
        else
        {
            switch (chon)
            {
            case 1:
                ql.AddEmployee();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 2:
                ql.EditEmployee();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 3:
                ql.displayInfor_ALL();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 4:
                ql.SreachEmployeeByID();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 5:
                ql.RemoveEmployeeByID();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 6:
                //ql.TimNhanVienTheoMa();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 7:
                //ql.XoaNhanVien();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 8:
                cout << "Thoat chuong trinh\n";
                ql.WriteToFile();
                break;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai!\n";
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            }
        }
    }
}

int main() {
    menu_QL_NhanVien();

    return 0;

}
