//
// Created by USER on 16/09/2023.
//

#include <iostream>
#include <string>
#include <cstring>
#include "iomanip"
using namespace std;

typedef struct material {
    string materialID, materialName, unit;
    int numberInStock;
}MATERIAL;

struct MaterialNodeTree {
    MATERIAL material;
    MaterialNodeTree* left;
    MaterialNodeTree* right;
    int height;
};
typedef MaterialNodeTree *MATERIAL_NODE_TREE;

MATERIAL_NODE_TREE NewNode (MATERIAL material) {
    MATERIAL_NODE_TREE node = new MaterialNodeTree;
    node->material = material;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int getMaterialNodeTreeHeight(MATERIAL_NODE_TREE root) {
    if (root == NULL) return 0;
    return root->height;
}

int getBalance(MATERIAL_NODE_TREE root) {
    if (root == NULL) return 0;
    return getMaterialNodeTreeHeight(root->left) - getMaterialNodeTreeHeight(root->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

MATERIAL_NODE_TREE rightRotate(MATERIAL_NODE_TREE y) {
    //
    MATERIAL_NODE_TREE x = y->left;
    y->left = x->right;
    x->right = y;
    x->height = max(getMaterialNodeTreeHeight(y->left), getMaterialNodeTreeHeight(y->right)) + 1;
    y->height = max(getMaterialNodeTreeHeight(x->left), getMaterialNodeTreeHeight(x->right)) + 1;
    return x;
}

MATERIAL_NODE_TREE leftRotate(MATERIAL_NODE_TREE x) {
    MATERIAL_NODE_TREE y = x->right;
    MATERIAL_NODE_TREE T2 = y->left;
    y->left = x;
    x->right = T2;
    // cap nhat chieu cao cay
    x->height = max(getMaterialNodeTreeHeight(x->left), getMaterialNodeTreeHeight(x->right)) + 1;
    y->height = max(getMaterialNodeTreeHeight(y->left), getMaterialNodeTreeHeight(y->right)) + 1;
    return y;
}

MATERIAL_NODE_TREE addMaterialTree(MATERIAL_NODE_TREE &node, MATERIAL material) {
    if(node == NULL) return (NewNode(material));
    if(strcmp(material.materialID.c_str(),node->material.materialID.c_str()) < 0)
        node->left= addMaterialTree(node->left, material);
    else if(strcmp(material.materialID.c_str(),node->material.materialID.c_str()) > 0)
        node->right= addMaterialTree(node->right,material);
    else return node;

    node->height = 1 + max(getMaterialNodeTreeHeight(node->left), getMaterialNodeTreeHeight(node->right));

    int balance = getBalance(node);
    // trai - trai
    if(balance > 1 && strcmp(material.materialID.c_str(),node->left->material.materialID.c_str()) < 0)
        return rightRotate(node);
    // phai - phai
    if (balance < -1 && strcmp(material.materialID.c_str(),node->right->material.materialID.c_str())>0)
        return leftRotate(node);
    // trai - phai
    if(balance > 1 && strcmp(material.materialID.c_str(),node->left->material.materialID.c_str()) > 0) {
        node->left = leftRotate((node->left));
        return rightRotate((node));
        }
    // phai - trai
    if(balance < -1 && strcmp(material.materialID.c_str(),node->right->material.materialID.c_str()) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
        }
    return node;
}

MATERIAL_NODE_TREE findMinValueNode(MATERIAL_NODE_TREE node) {
    MATERIAL_NODE_TREE current = node;

    while (current->left != NULL)
        current = current->left;
    return current;
}

MATERIAL_NODE_TREE deleteMaterialByID(MATERIAL_NODE_TREE &root, string materialId) {
    if(root == NULL)
        return root;
    if(strcmp(materialId.c_str(),root->material.materialID.c_str()) < 0)
        root->left = deleteMaterialByID(root->left,materialId);
    else if(strcmp(materialId.c_str(),root->material.materialID.c_str())>0)
        root->right = deleteMaterialByID(root->right,materialId);
    else {
        if ((root->left == NULL) || (root->right == NULL))
        {
            MATERIAL_NODE_TREE temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            delete temp;
        } else
        {
            MATERIAL_NODE_TREE temp = findMinValueNode(root->right);
            // Copy the inorder successor's data to this node
            root->material = temp->material;
            // Delete the inorder successor
            root->right = deleteMaterialByID(root->right, temp->material.materialID);
        }
    }
    // If the tree had only one node then return
    if (root == NULL) return root;

    root->height = 1 + max(getMaterialNodeTreeHeight(root->left), getMaterialNodeTreeHeight(root->right));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void deleteTree(MATERIAL_NODE_TREE &root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

MATERIAL inputMaterial() {
    MATERIAL result;
    cin.ignore();
    cout << "Nhap ma vat tu: ";
    getline(cin, result.materialID);
    cout << "Nhap ten vat tu: ";
    getline(cin, result.materialName);
    cout << "Nhap don vi tinh: ";
    getline(cin, result.unit);
    cout << "Nhap so luong ton: ";
    cin >> result.numberInStock;
    cout << "\n";
    return result;
}

void materialTitle() {
    cout << "\n============================================================================================\n";
    cout << setw(17) << left << "Ten vat tu" << "\t";
    cout << setw(17) << left << "Ma vat tu" << "\t";
    cout << setw(17) << left << "So luong ton" << "\t";
    cout << setw(17) << left << "Don vi tinh" << "\t";
    cout << "\n============================================================================================\n";
}

void printMaterial(MATERIAL material) {
    cout << setw(17) << left << material.materialName << "\t";
    cout << setw(17) << left << material.materialID << "\t";
    cout << setw(17) << left << material.numberInStock << "\t";
    cout << setw(17) << left << material.unit  << "\t" << endl;
}

void preOrder(MATERIAL_NODE_TREE root) {
    if (root != NULL) {
        printMaterial(root->material); // Xuất thông tin của một nút
        preOrder(root->left); // Duyệt và xuất cây con bên trái
        preOrder(root->right); // Duyệt và xuất cây con bên phải
    }
}

bool findMaterial(MATERIAL_NODE_TREE root, string value) {
    if (root == NULL)
        return false;

    int comparison = strcmp(value.c_str(), root->material.materialID.c_str());
    if (comparison == 0)
        return true; // Trả về true nếu tìm thấy giá trị
    else if (comparison < 0)
        return findMaterial(root->left, value);
    else
        return findMaterial(root->right, value);
}

MATERIAL_NODE_TREE findMaterialByID(MATERIAL_NODE_TREE root, string value) {
    if (root == NULL)
        return NULL;

    int comparison = strcmp(value.c_str(), root->material.materialID.c_str());
    if (comparison == 0)
        return root; // Trả về con trỏ nếu tìm thấy giá trị
    else if (comparison < 0)
        return findMaterialByID(root->left, value);
    else
        return findMaterialByID(root->right, value);
}


MATERIAL_NODE_TREE adjustMaterialInfo(MATERIAL_NODE_TREE &root, string materialID) {

    MATERIAL_NODE_TREE foundNode = findMaterialByID(root, materialID);

    if (foundNode != NULL) {
        int choice;
        do {
            cout << "\n=========== Menu Hieu Chinh Thong Tin ===========\n";
            cout << "1. Hieu chinh ten vat tu\n";
            cout << "2. Hieu chinh don vi tinh\n";
            cout << "3. Hieu chinh so luong ton (chi ap dung khi vat tu la moi)\n";
            cout << "0. Quay lai\n";
            cout << "Nhap lua chon cua ban: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Nhap ten vat tu moi: ";
                    cin.ignore();
                    getline(cin, foundNode->material.materialName);
                    cout << "Hieu chinh ten vat tu thanh cong!\n";
                    break;
                case 2:
                    cout << "Nhap don vi tinh moi: ";
                    cin.ignore();
                    getline(cin, foundNode->material.unit);
                    cout << "Hieu chinh don vi tinh thanh cong!\n";
                    break;
                case 3:
                    // Chỉ cho phép hieu chinh so luong ton khi vat tu la moi
                    if (foundNode->material.numberInStock == 0) {
                        cout << "Nhap so luong ton moi: ";
                        cin >> foundNode->material.numberInStock;
                        cout << "Hieu chinh so luong ton thanh cong!\n";
                    } else {
                        cout << "Khong the hieu chinh so luong ton cho vat tu da co ton kho!\n";
                    }
                    break;
                case 0:
                    cout << "Da quay lai Menu chinh.\n";
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai!\n";
            }

        } while (choice != 0);
        cout << "Cap nhat thong tin vat tu thanh cong!\n";
    } else {
        cout << "Vat tu khong ton tai.\n";
    }
    return root;
}


// float findMaxRevenueMaterial(employeeList employeeList) {
//     float maxMaterialRevenue = 0;

//     // Duyệt qua danh sách nhân viên
//     for (int i = 0; i < employeeList.numberEmployee; ++i) {
//         BILL_NODE currentBill = employeeList.employeeNode[i]->billList;

//         // Duyệt qua danh sách hóa đơn của nhân viên
//         while (currentBill != NULL) {
//             BILL_DETAIL_NODE currentDetail = currentBill->bill->listBillDetail;

//             // Duyệt qua danh sách chi tiết hóa đơn
//             while (currentDetail != NULL) {
//                 float currentMaterialRevenue = calculateRevenue(currentDetail);

//                 // So sánh và cập nhật doanh thu cao nhất
//                 if (currentMaterialRevenue > maxMaterialRevenue) {
//                     maxMaterialRevenue = currentMaterialRevenue;
//                 }

//                 currentDetail = currentDetail->next;
//             }

//             currentBill = currentBill->next;
//         }
//     }

//     return maxMaterialRevenue;
// }
