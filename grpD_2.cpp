/*A Dictionary stores keywords and its meanings. Provide facility for adding new
keywords, deleting keywords, updating values of any entry. Provide facility to display
whole data sorted in ascending/ Descending order. Also find how many maximum
comparisons may require for finding any keyword. Use Height balance tree and find the
complexity for finding a keyword.
*/

#include<iostream>
using namespace std;
class Node
{
    public:
    Node *left,*right;
    string key,val;
    int height;
};
class avl
{
    public:
    Node *create(Node *root,string key, string val){
        root=new Node();
        root->key=key;
        root->val=val;
        root->left=NULL;
        root->right=NULL;
        root->height=1;
        return root;
    }

    Node *insert(Node *root,string key, string val){
        if (root==NULL)
        return create(root,key,val);
        else if(key<root->key){
            root->left = insert(root->left,key,val);
        }
        else if(key>root->key){
            root->right = insert(root->right,key,val);
        }
        return root;
    }

    int height(Node *temp){
        int h=0;
        if(temp!=NULL){
            int l_height=height(temp->left);
            int r_height=height(temp->right);
            int max_height=max(l_height,r_height);
            h=max_height+1;
        }
        return h;
    }

    int balFac(Node *temp){
        int l_height=height(temp->left);
        int r_height=height(temp->right);
        int b_factor=l_height-r_height;
        return b_factor;
    }

    Node *rr(Node *root){
        Node *temp;
        temp=root->right;
        root->right=temp->left;
        temp->left=root;
        return temp;
    }

    Node *ll(Node *root){
        Node *temp;
        temp=root->left;
        root->left=temp->right;
        temp->right=root;
        return temp;
    }

    Node *lr(Node *root){
        Node *temp;
        temp=root->left;
        root->left=rr(temp);
        return ll(root);
    }

    Node *rl(Node *root){
        Node *temp;
        temp=root->left;
        root->right=ll(temp);
        return rr(root);
    }

    Node *balance(Node *root){
        int bal_factor=balFac(root);
        if(bal_factor>1){
            if(balFac(root->left)>0)
                root=ll(root);
            else
                root=lr(root);
        }
        else if(bal_factor<-1){
            if(balFac(root->right)>0)
                root=rl(root);
            else
            root=rr(root);
        }
        return root;
    }

    void inorder(Node *root){
        if(root==NULL)
        return;
        inorder(root->left);
        cout<<root->key<<" "<<root->val<<endl;
        inorder(root->right);
    }

    void modify(Node *root, string modkey){
        string NewMeaning;
        if(modkey.compare(root->key)<0)
        modify(root->left,modkey);
        else if(modkey.compare(root->key)>0)
        modify(root->right,modkey);
        else if(modkey.compare(root->key)==0){
            cout<<"\n Word Found! \n word: "<<root->key<<"\t"<<root->val;
            cout<<"\n Enter new Meaning: ";
            cin>>NewMeaning;
            root->val=NewMeaning;
            cout<<"\n Dictionary Modified!";
        }
    }

    void delet(Node *root,string delkey){
        Node *current=root;
        Node *temp;
        bool isleft=0;
        while(current!=NULL && current->key.compare(delkey)!=0){
            if(current->key.compare(delkey)>0){
                temp = current;
                isleft=1;
                current=current->left;
            }
            else if(current->key.compare(delkey)<0){
                temp=current;
                isleft=0;
                current=current->right;
            }
        }
        if (current->key.compare(delkey)==0){
            if(current->left==NULL && current->right==NULL){
                if(isleft==1){
                    temp->left=NULL;
                }
                else
                temp->right=NULL;
            }
            else{
                if(isleft==1){
                    if(current->left==NULL){
                        temp->left==current->right;
                    }
                    else if(current->right==NULL){
                        temp->left=current->left;
                    }
                    else{
                        string k =current->left->key;
                        string v =current->left->val;
                        temp->left=current->right;
                        insert(root,k,v);
                    }
                }
                else{
                    if(current->left==NULL){
                        temp->right=current->right;
                    }
                    else if(current->right==NULL){
                        temp->right=current->left;
                    }
                    else{
                        string k=current->left->key;
                        string v=current->left->val;
                        temp->right=current->right;
                        insert(root,k,v);
                    }
                }
            }
            cout<<"\n Deleted!";
        }
        else{
            cout<<"\n Word not Found!";
        }
        return;
    }
};
int main()
{
    int choice,dchoice;
    string key,val,modkey,delkey;
    Node *root=new Node();
    avl avlobj;
    do
    {
        cout<<"MENU";
        cout<<"\n 1.Add word \n 2.Delete word \n 3.Update word \n 4.Display \n 5.Exit";
        cout<<"\n Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
            cout<<"\n Enter the word and meaning: ";
            cin>>key>>val;
            root=avlobj.insert(root,key,val);
            break;

            case 2:
            cout<<"\n Enter the word you want to delete: ";
            cin>>delkey;
            avlobj.delet(root,delkey);
            break;
            
            case 3:
            cout<<"\n Enter the word you want to modify: ";
            cin>>modkey;
            avlobj.modify(root, modkey);
            break;

            case 4:
            avlobj.inorder(root);
            break;

            case 5:
            exit(0);

            default:
            cout<<"\n Invalid option";
        }

    } while (choice!=5);
    return 0;
}
