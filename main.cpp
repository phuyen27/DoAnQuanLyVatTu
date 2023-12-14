#include "Employee.cpp"

using namespace std;

int main() {
    MATERIAL_NODE_TREE root;
    root = NULL;
    
    employeeList employeeList;
    cout << "Chuong trinh quan ly vat tu\n";
    int userChoose;
    do {
        cout << "Cac chuc nang cua chuong trinh la\n";
        cout << "1. Cap nhat vat tu(them, xoa, sua thong tin)\n";
        cout << "2. Xuat danh sach vat tu\n";
        cout << "3. Nhap thong tin nhan vien\n";
        cout << "4. Nhap hoa don va chi tiet hoa don cua nhan vien\n";
        cout << "5. Xuat thong tin nhan vien theo thu tu ten\n";
        cout << "6. Xuat thong tin hoa don va chi tiet hoa don\n";
        cout << "7. Xuat chi phi cua tung hoa don\n";
        cout << "Ban hay nhap lua chon cua minh: ";
        cin >> userChoose;
        switch (userChoose) {
            case 1:
            {
                int materialChoose;
                do {
                    cout << "\nHay chon cach cap nhat vat tu: \n";
                    cout << "1. Them vat tu.\n";
                    cout << "2. Xoa vat tu (dua vao ma vat tu).\n";
                    cout << "3. Chinh sua thong tin vat tu.\n";
                    cout << "Ban hay nhap lua chon cua minh! ";
                    cin >> materialChoose;
                    if(materialChoose == 1) {
                        MATERIAL material = inputMaterial();
                        root = addMaterialTree(root, material);
                    }
                    if(materialChoose == 2) {
                        string materialID;
                        cout << "\nNhap ma vat tu muon xoa: ";
                        cin.ignore();
                        getline(cin, materialID);
                        root = deleteMaterialByID(root, materialID);
                        cout << "\nDa xoa vat tu!";
                    }
                    if(materialChoose == 3) {
                        string materialID;
                        cout << "\nNhap ma vat tu muon cap nhat: ";
                        cin.ignore();
                        getline(cin, materialID);
                        root = adjustMaterialInfo(root, materialID);
                    }

                } while (materialChoose > 3);
                break;
            }
            case 2:
                cout << "\n\t\t\tDANH SACH VAT TU";
                materialTitle();
                preOrder(root);
                break;
            case 3:
                addEmployeeList(employeeList);
                break;
            case 4:
            {
                char choose;
                do{
                    string employeeId;
                    cout << "\nNhap ma so nhan vien muon lap hoa don: ";
                    cin.ignore();
                    getline(cin, employeeId);
                    int temp = searchEmployee(employeeList, employeeId);
                    if(temp == -1) {
                        cout << "\nMa so nhan vien khong hop le! Ban co muon nhap tiep khong? (y/n): ";
                        cin >> choose;
                    }
                    else {
                        inputAllBill(employeeList.employeeNode[temp]->billList,root);
                        cout << "\nBan co muon nhap tiep khong? (y/n): ";
                        cin >> choose;
                    }
                }while(choose == 'y');
                break;
            }
            case 5:
                outputListEmployee(employeeList);
                break;
            case 6:
                outputBillEmployee(employeeList);
                break;
            case 7:
            {
                for(int i = 0; i < employeeList.numberEmployee; i++) {
                outputInvoiceCost(employeeList.employeeNode[i]->billList);
                }
                break;
            }
            default:
                cout << "\nChuc nang khong co san!";
                break;
        }
    } while (userChoose > 0);
    deleteTree(root);
    return 0;
}
