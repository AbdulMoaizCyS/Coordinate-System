#include<iostream>
#include<exception>
#include<vector>
#include<cmath>
#include<utility>
#include<tuple>
#include<limits>
#include<fstream>

const double epsilon = 0.0001;
// ===================
//      CLASSES 
// ===================
class GraphingClass;
class FileHandler;
class Point2D{
    private:
        double x;
        double y;
    public:
        // ===================
        //    CONSTRUCTORS 
        // ===================
        Point2D(){
            x=0.00;
            y=0.00;
        }
        Point2D(double a,double b){
            x=a;
            y=b;
        }
        Point2D(const Point2D& obj){
            x = obj.x;
            y = obj.y;
        }
        // ===================
        //   CORE OPERATIONS 
        // ===================
        double Distance(const Point2D& obj);
        std::pair<double,double> Midpoint(const Point2D& obj);
        void Display();
        void GraphPoint();
        // ===================
        // OPERATOR OVERLOADING 
        // ===================
        Point2D operator+(double a){
            double X = this->x + a;
            double Y = this->y + a;

            Point2D Point(X,Y);
            return Point;
        }
        Point2D operator-(const Point2D& obj){
            double X = this->x - obj.x;
            double Y = this->y - obj.y;

            Point2D Point(X,Y);
            return Point;
        }
        Point2D operator-(double a){
            double X = this->x - a;
            double Y = this->y - a;

            Point2D Point(X,Y);
            return Point;
        }
        Point2D operator*(double a){
            double X = a * this->x;
            double Y = a * this->y;

            Point2D Point(X,Y);
            return Point;
        }
        Point2D operator/(double a){
            double X,Y;
            do{
                if(a==0){
                    std::cout << "ERROR! CAN NOT DIVIDE BY ZERO!\n";
                    std::cout << "ENTER AGAIN!\n";
                    std::cin >> a;
                }else{
                    X = this->x/a;
                    Y = this->y/a;
                break;
                }
            }while(1);
            Point2D Point(X,Y);
            return Point;
        }
        bool operator==(const Point2D& obj) const{
            if((std::abs(this->x - obj.x)<epsilon) && (std::abs(this->y - obj.y)<epsilon)){
                return 1;
            }else{
                return 0;
            }
        }
        friend FileHandler;
};
class Point3D{
    private:
        double x;
        double y;
        double z;
    public:
        // ===================
        //    CONSTRUCTORS 
        // ===================
        Point3D(){
            x=0.00;
            y=0.00;
            z=0.00;
        }
        Point3D(double a,double b,double c){
            x=a;
            y=b;
            z=c;
        }
        Point3D(const Point3D& obj){
            x = obj.x;
            y = obj.y;
            z = obj.z;
        }
        // ===================
        //   CORE OPERATIONS 
        // ===================
        double Distance(const Point3D& obj);
        std::tuple<double,double,double> Midpoint(const Point3D& obj);
        void Display();
        // ===================
        // OPERATOR OVERLOADING 
        // ===================
        Point3D operator+(double a){
            double X = this->x + a;
            double Y = this->y + a;
            double Z = this->z + a;

            Point3D Point(X,Y,Z);
            return Point;
        }
        Point3D operator-(const Point3D& obj){
            double X = this->x - obj.x;
            double Y = this->y - obj.y;
            double Z = this->z - obj.z;

            Point3D Point(X,Y,Z);
            return Point;
        }
        Point3D operator-(double a){
            double X = this->x - a;
            double Y = this->y - a;
            double Z = this->z - a;

            Point3D Point(X,Y,Z);
            return Point;
        }
        Point3D operator*(double a){
            double X = a * this->x;
            double Y = a * this->y;
            double Z = a * this->z;

            Point3D Point(X,Y,Z);
            return Point;
        }
        Point3D operator/(double a){
            double X,Y,Z;
            do{
                if(a==0){
                    std::cout << "ERROR! CAN NOT DIVIDE BY ZERO!\n";
                    std::cout << "ENTER AGAIN!\n";
                    std::cin >> a;
                }else{
                    X = this->x/a;
                    Y = this->y/a;
                    Z = this->z/a;
                break;
                }
            }while(1);

            Point3D Point(X,Y,Z);
            return Point;
        }
        bool operator==(const Point3D& obj) const{
            if((std::abs(this->x - obj.x)<epsilon) && (std::abs(this->y - obj.y)<epsilon) && ((std::abs(this->z - obj.z)<epsilon))){
                return 1;
            }else{
                return 0;
            }
        }
        friend FileHandler;
};

class Manager{
    public:
        virtual void AddPoint()=0;
        virtual void RemovePoint()=0;
        virtual void ListAllPoints()=0;
        virtual void DistanceBetweenPoints()=0;
        virtual void Midpoint()=0;
        virtual void DisplayPoint()=0;
        virtual void PointManipulation()=0;
        virtual ~Manager()=default;
};
class TwoDManager : public Manager{
    private:
        std::vector<Point2D> TwoDList;
    public:
        void AddPoint();
        void DisplayPoint();
        void ListAllPoints();
        void RemovePoint();
        void DistanceBetweenPoints();
        void Midpoint();
        void PointManipulation();
        void Graph();
        void AddTwoDList(std::vector<Point2D> List);
        friend FileHandler;

};
class ThreeDManager : public Manager{
    private:
        std::vector<Point3D> ThreeDList;
    public:
        void AddPoint();
        void DisplayPoint();
        void ListAllPoints();
        void RemovePoint();
        void DistanceBetweenPoints();
        void Midpoint();
        void PointManipulation();
        void AddThreeDList(std::vector<Point3D> List);
        friend FileHandler;
};

// ===================
//   2D POINT VIEWER 
// ===================

class GraphingClass{
    private:
        char** Array;
        double PointX,PointY;
        int maxX,maxY;
        int PlotX,PlotY;
        double scale;
    public:
        GraphingClass(double a=0.0,double b=0.0,double c=2.0) : PointX(a),PointY(b),scale(c){
            PlotX=std::round(PointX*scale);
            PlotY=std::round(PointY*scale);
            maxX=std::abs(PlotX)+5;
            maxY=std::abs(PlotY)+5;
            Array = new char*[maxY];
            for(int i=0;i<maxY;i++){
                Array[i] = new char[maxX];
            }
            Initialise();
        }
        void Initialise(){
            for(int i=0;i<maxY;i++){
                for(int j=0;j<maxX;j++){
                    Array[i][j] = '.';
                }
            }
        }
        void Output(){
            for(int i=0;i<maxY;i++){
                for(int j=0;j<maxX;j++){
                    std::cout << Array[i][j];
                }
                std::cout << std::endl;
            }
        }
        void Draw(){
            if(PlotX<0){
                if(PlotY<0){
                    for(int i=0;i<maxY;i++){
                        for(int j=0;j<maxX;j++){
                            if(i==0){
                                Array[i][j] = '-';
                                Array[i][maxX-1] = '+';
                            }else if(j==maxX-1){
                                Array[i][j] = '|';
                            }else{
                                Array[i][j] = ' ';
                            }
                            if(i==std::abs(PlotY) && j==std::abs(PlotX)){
                                Array[i][j] = '@';
                            }
                        }
                    }
                    
                }else if(PlotY>0){
                    for(int i=0;i<maxY;i++){
                        for(int j=0;j<maxX;j++){
                            if(i==maxY-1){
                                Array[i][j] = '-';
                                Array[i][maxX-1] = '+';
                            }else if(j==maxX-1){
                                Array[i][j] = '|';
                            }else{
                                Array[i][j] = ' ';
                            }
                            if(i==std::abs(PlotY) && j==std::abs(PlotX)){
                                Array[i][j] = '@';
                            }
                        }
                    }

                }else if(PlotY==0){
                    for(int i=0;i<maxY;i++){
                        for(int j=0;j<maxX;j++){
                            if(i==maxY-1){
                                Array[i][j] = '-';
                                Array[i][maxX-1] = '+';
                            }else if(j==maxX-1){
                                Array[i][j] = '|';
                            }else{
                                Array[i][j] = ' ';
                            }
                            if(i==maxY-1 && j==std::abs(PlotX)){
                                Array[i][j] = '@';
                            }
                        }
                    }
                }
            }else if(PlotX>0){
                if(PlotY<0){
                    for(int i=0;i<maxY;i++){
                        for(int j=0;j<maxX;j++){
                            if(i==0){
                                Array[i][j] = '-';
                                Array[i][0] = '+';
                            }else if(j==0){
                                Array[i][j] = '|';
                            }else{
                                Array[i][j] = ' ';
                            }
                            if(i==std::abs(PlotY) && j==std::abs(PlotX)){
                                Array[i][j] = '@';
                            }
                        }
                    }
                }else if(PlotY>0){
                    for(int i=0;i<maxY;i++){
                        for(int j=0;j<maxX;j++){
                            if(i==maxY-1){
                                Array[i][j] = '-';
                                Array[i][0] = '+';
                            }else if(j==0){
                                Array[i][j] = '|';
                            }else{
                                Array[i][j] = ' ';
                            }
                            if(i==std::abs(PlotY) && j==std::abs(PlotX)){
                                Array[i][j] = '@';
                            }
                        }
                    }
                }else if(PlotY==0){
                    for(int i=0;i<maxY;i++){
                        for(int j=0;j<maxX;j++){
                            if(i==maxY-1){
                                Array[i][j] = '-';
                                Array[i][0] = '+';
                            }else if(j==0){
                                Array[i][j] = '|';
                            }else{
                                Array[i][j] = ' ';
                            }
                            if(i==maxY-1 && j==std::abs(PlotX)){
                                Array[i][j] = '@';
                            }
                        }
                    }
                }
            }else if(PlotX==0){
                if(PlotY<0){
                    for(int i=0;i<maxY;i++){
                        for(int j=0;j<maxX;j++){
                            if(i==0){
                                Array[i][j] = '-';
                                Array[i][0] = '+';
                            }else if(j==0){
                                Array[i][j] = '|';
                            }else{
                                Array[i][j] = ' ';
                            }
                            if(i==std::abs(PlotY) && j==0){
                                Array[i][j] = '@';
                            }
                        }
                    }
                }else if(PlotY>0){
                    for(int i=0;i<maxY;i++){
                        for(int j=0;j<maxX;j++){
                            if(i==maxY-1){
                                Array[i][j] = '-';
                                Array[i][0] = '+';
                            }else if(j==0){
                                Array[i][j] = '|';
                            }else{
                                Array[i][j] = ' ';
                            }
                            if(i==std::abs(PlotY) && j==0){
                                Array[i][j] = '@';
                            }
                        }
                    }
                }
            }else{
                for(int i=0;i<maxY;i++){
                    for(int j=0;j<maxX;j++){
                        if(i==maxY-1){
                            Array[i][j] = '-';
                            Array[i][int(maxX/2.0)]='@';
                        }else if(j==int(maxX/2.0)){
                            Array[i][j]='|';
                        }else{
                            Array[i][j] = ' ';
                        }
                    }
                }
            }
        }
        ~GraphingClass(){
            for(int i=0;i<maxY;i++){
                delete[] Array[i];
            }
            delete[] Array;
        }

};
// ====================
//  FILE HANDLER CLASS 
// ====================
class FileHandler{
    private:
        std::string TwoDFilepath;
        std::string ThreeDFilepath;
    public:
        void Set2DPath(std::string path);
        void Set3DPath(std::string path);
        void InputToTwoDFile(const TwoDManager &obj);
        std::vector<Point2D> ReadFromTwoDFile();
        void InputToThreeDFile(const ThreeDManager &obj);
        std::vector<Point3D> ReadFromThreeDFile();
};
// ===================
// FUNCTION DEFINITIONS 
//   HELPER FUNCTIONS
// ===================
std::pair<int,int>DoubleInputHandler(){ //FOR THE INDEX OF TWO POINTS, i.e USER IS ASKED TO ENTER INDICES OF WHICH TOW POINTS THEY WOULD LIKE TO MANIPULATE(ERROR HANDLING!)
    std::string a,b;

    do{
    try{
        std::cout << "PLEASE INPUT THE INDEX OF THE TWO POINTS!: ";
        std::cin >> a >> b;

        int x = std::stoi(a);
        int y = std::stoi(b);
        if(x<0 || y<0){
            throw(1);
        }

        return {x,y};

    }
    catch(...){
        std::cout << "INVALID INPUT!!!! PLEASE TRY AGAIN!!!!\n";
    }

    }while(1);



}
int SingleInputHandler(){ //SAME FUNCTIONALITY AS DoubleInputHandler BUT FOR A SINGLE POINT INDEX!(ERROR HANDLING!)
    std::string a;

    do{
    try{
        std::cout << "PLEASE INPUT THE INDEX OF THE POINT!: ";
        std::cin >> a;

        int x = std::stoi(a);
        if(x<0){
            throw(1);
        }

        return x;

    }
    catch(...){
        std::cout << "INVALID INPUT!!!! PLEASE TRY AGAIN!!!!\n";
    }

    }while(1);

}
double PointInputHandler(){
    double temp;
    
    do{
        std::cout << "PLEASE ENTER THE CO-ORDINATE!:\n";
        if(std::cin >> temp){
            return temp;
        }else{
            std::cout << "INVALID INPUT!!! TRY AGAIN!!!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        }
    }while(true);
}

int main(){
    TwoDManager Manager1;
    ThreeDManager Manager2;
    FileHandler FileManager;
    std::string choice1;

    do{
        std::cout << "PLEASE ENTER 1 TO GO TO THE 2D-POINT MENU!\n";
        std::cout << "PLEASE ENTER 2 TO GO THE THE 3D-POINT MENU!\n";
        std::cout << "PLEASE ENTER 3 TO GO TO THE FILING MENU!\n";
        std::cout << "ENTER '-1' TO EXIST THE SYSTEM!\n";
        std::cin >> choice1;
        if(choice1=="1"){
            std::string choice2;
            do{
                std::cout << "----2D POINT MANAGER!----\n";
                std::cout << "---->PRESS 1 TO ADD A POINT!<----\n";
                std::cout << "---->PRESS 2 TO DISPLAY A POINT!<----\n";
                std::cout << "---->PRESS 3 TO DISPALY ALL POINTS!<----\n";
                std::cout << "---->PRESS 4 TO REMOVE A POINT!<----\n";
                std::cout << "---->PRESS 5 TO FIND DISTANCE B/W TWO POINTS!<----\n";
                std::cout << "---->PRESS 6 TO FIND MIDPOINT B/W TWO POINTS!<----\n";
                std::cout << "---->PRES 7 TO GO THE POINT MANIPULATION MENU!<----\n";
                std::cout << "---->PRESS 8 TO DISPLAY A POINT IN IT'S QUADRANT!<----\n";
                std::cout << "---->PRESS -1 TO EXIT THE 2D POINT MANAGER MENU!<----\n";
                std::cin >> choice2;
                if(choice2=="1"){
                    Manager1.AddPoint();
                }else if(choice2 =="2"){
                    Manager1.DisplayPoint();
                }else if(choice2=="3"){
                    Manager1.ListAllPoints();
                }else if(choice2=="4"){
                    Manager1.RemovePoint();
                }else if(choice2=="5"){
                    Manager1.DistanceBetweenPoints();
                }else if(choice2=="6"){
                    Manager1.Midpoint();
                }else if(choice2=="7"){
                    Manager1.PointManipulation();
                }else if(choice2=="8"){
                    Manager1.Graph();
                }else if(choice2=="-1"){
                    std::cout << "----EXITING THE 2D MANAGER MENU!----\n";
                }else{
                    std::cout << "----INVALID INPUT!!! TRY AGAIN!!!!----\n";
                }
            }while(choice2!="-1");
        }else if(choice1=="2"){
            std::string choice3;
            do{
                std::cout << "----3D POINT MANAGER!----\n";
                std::cout << "---->PRESS 1 TO ADD A POINT!<----\n";
                std::cout << "---->PRESS 2 TO DISPLAY A POINT!<----\n";
                std::cout << "---->PRESS 3 TO DISPALY ALL POINTS!<----\n";
                std::cout << "---->PRESS 4 TO REMOVE A POINT!<----\n";
                std::cout << "---->PRESS 5 TO FIND DISTANCE B/W TWO POINTS!<----\n";
                std::cout << "---->PRESS 6 TO FIND MIDPOINT B/W TWO POINTS!<----\n";
                std::cout << "---->PRES 7 TO GO THE POINT MANIPULATION MENU!<----\n";
                std::cout << "---->PRESS -1 TO EXIT THE 3D POINT MANAGER MENU!<----\n";
                std::cin >> choice3;

                if(choice3=="1"){
                    Manager2.AddPoint();
                }else if(choice3=="2"){
                    Manager2.DisplayPoint();
                }else if(choice3=="3"){
                    Manager2.ListAllPoints();
                }else if(choice3=="4"){
                    Manager2.RemovePoint();
                }else if(choice3=="5"){
                    Manager2.DistanceBetweenPoints();
                }else if(choice3=="6"){
                    Manager2.Midpoint();
                }else if(choice3=="7"){
                    Manager2.PointManipulation();
                }else if (choice3=="-1"){
                    std::cout << "----EXITING THE 3D MANAGER MENU!----\n";
                }else{
                    std::cout << "----INVALID INPUT!!! TRY AGAIN!!!!----\n";
                }
            }while(choice3!="-1");
        }else if(choice1=="3"){
            std::string choice4;
            std::cout << "----FILE MANAGER MENU!----\n";
            std::cout << "ENTER 1 TO GO TO 2D FILE MANAGER MENU!\n";
            std::cout << "ENTER 2 TO GO TO 3D FILE MANAGER MENU!\n";
            std::cout << "ENTER -1 TO EXIT FILE MANAGER MENU!\n";
            std::cin >> choice4;
            do{
                if(choice4=="1"){
                    std::string twodpath;
                    std::string choice5;
                    std::cout << "----2D FILE MANAGER MENU!----\n";
                    std::cout << "PLEASE ENTER THE PATH OF THE 2D FILE WHERE DATA WILL BE STORED/MANIPULATED!\n";
                    std::cin >> twodpath;
                    FileManager.Set2DPath(twodpath);
                    do{
                        std::cout << "ENTER 1 IF YOU WANT TO INPUT DATA TO FILE!\n";
                        std::cout << "ENTER 2 IF YOU WANT TO READ DATA FROM FILE!\n";
                        std::cout << "ENTER -1 IF YOU WANT TO EXIT 2D FILE MANAGER MENU!\n";
                        std::cin >> choice5;
                        if(choice5=="1"){
                            FileManager.InputToTwoDFile(Manager1);
                        }else if(choice5=="2"){
                            std::vector<Point2D> list;
                            list = FileManager.ReadFromTwoDFile();
                            Manager1.AddTwoDList(list);
                        }else if(choice5=="-1"){
                                std::cout << "EXITING 2D FILE MANAGER MENU!\n";
                        }else{
                            std::cout << "INVALID CHOICE!\n";
                        }
                    }while(choice5!="-1");
                    break;
                }else if(choice4=="2"){
                    std::string ThreeDPath;
                    std::string choice6;
                    std::cout << "----3D FILE MANAGER MENU!----\n";
                     std::cout << "PLEASE ENTER THE PATH OF THE 3D FILE WHERE DATA WILL BE STORED/MANIPULATED!\n";
                    std::cin >> ThreeDPath;
                    FileManager.Set3DPath(ThreeDPath);
                    do{
                        std::cout << "ENTER 1 IF YOU WANT TO INPUT DATA TO FILE!\n";
                        std::cout << "ENTER 2 IF YOU WANT TO READ DATA FROM FILE!\n";
                        std::cout << "ENTER -1 IF YOU WANT TO EXIT 3D FILE MANAGER MENU!\n";
                        std::cin >> choice6;
                        if(choice6=="1"){
                            FileManager.InputToThreeDFile(Manager2);
                        }else if(choice6=="2"){
                            std::vector<Point3D> list;
                            list = FileManager.ReadFromThreeDFile();
                            Manager2.AddThreeDList(list);
                        }else if(choice6=="-1"){
                            std::cout << "EXITING 3D FILE MANAGER MENU!\n";
                        }else{
                            std::cout << "INVALID CHOICE!\n";
                        }
                    }while(choice6!="-1");
                    break;
                }else if(choice4=="-1"){
                    std::cout << "EXITING FILE MANAGER MENU!\n";
                }else{
                    std::cout << "INVALID CHOICE!\n";
                }
            }while(choice4!="-1");
        }else if(choice1=="-1"){
            std::cout << "----EXITING THE CO-ORDINATE SYSTEM!----\n";
        }else{
            std::cout << "----INVALID INPUT!!!! TRY AGAIN!!!!----\n";
        }
    }while(choice1!="-1");

    return 0;
}
// ===================
// FUNCTION DEFINITIONS 
//      POINT 2D
// ===================
double Point2D::Distance(const Point2D& obj){
    double X = pow((obj.x - x),2.0);
    double Y = pow((obj.y - y),2.0);

    return sqrt(X+Y);
}
std::pair<double,double> Point2D::Midpoint(const Point2D& obj){
    double X = (x + obj.x)/2;
    double Y = (y + obj.y)/2;

    return {X,Y};
}
void Point2D::Display(){
    std::cout << "POSITION ON X-AXIS: " << x << std::endl;
    std::cout << "POSITION ON Y-AXIS: " << y << std::endl;
    std::cout << "POINT CO-ORDINATES: " << '(' << x << ',' << y << ')' << std::endl;
}
void Point2D::GraphPoint(){
    GraphingClass d(x,y);
    d.Initialise();
    d.Draw();
    d.Output();
}
// ===================
// FUNCTION DEFINITIONS 
//      POINT 3D
// ===================
double Point3D::Distance(const Point3D& obj){
    double X = pow((obj.x - x),2.00);
    double Y = pow((obj.y - y),2.00);
    double Z = pow((obj.z - z),2.00);

    return sqrt(X+Y+Z);
}
std::tuple<double,double,double> Point3D::Midpoint(const Point3D& obj){
    double X = (x + obj.x)/2;
    double Y = (y + obj.y)/2;
    double Z = (z + obj.z)/2;

    return {X,Y,Z};
}
void Point3D::Display(){
    std::cout << "POSITION ON X-AXIS: " << x << std::endl;
    std::cout << "POSITION ON Y-AXIS: " << y << std::endl;
    std::cout << "POSITION ON Z-AXIS: " << z << std::endl;
    std::cout << "POINT CO-ORDINATES: " << '(' << x << ',' << y << ',' << z << ')' << std::endl;
}
// ===================
// TWO DIMENSION MANAGER 
//  FUNCTION DEFINIIONS
// ===================
void TwoDManager::AddPoint(){
    double a,b;

    std::cout << "PLEASE ENTER THE X COORDINATE OF 2D-POINT: ";
    a=PointInputHandler();
    std::cout << "PLEASE ENTER THE Y COORDINATE OF 2D-POINT: ";
    b=PointInputHandler();

    Point2D Temp(a,b);
    TwoDList.push_back(Temp);
    std::cout << "POINT SUCCESSFULLY ADDED TO 2D-LIST!\n";

}
void TwoDManager::DisplayPoint(){
    int i;
    std::cout << "INDEX ARE (0-"<<(TwoDList.size()-1)<<")" << std::endl;
    i = SingleInputHandler();
    std::cout << "2D-POINT AT INDEX " << i << " =>" << std::endl;
    TwoDList[i].Display();
}
void TwoDManager::ListAllPoints(){
    int max = TwoDList.size();

    for(int i=0;i<max;i++){
        std::cout << "INDEX=>" << i << std::endl;
        TwoDList[i].Display();
    }
}
void TwoDManager::RemovePoint(){
    int i=0;
    std::cout << "INDEX ARE (0-"<<(TwoDList.size()-1)<<")" << std::endl;
    i = SingleInputHandler();

    TwoDList.erase(TwoDList.begin()+i);
    std::cout << "2D-POINT AT INDEX " << i << "REMOVED SUCCESSFULLY!\n";
}
void TwoDManager::DistanceBetweenPoints(){
    int i=0,j=0;
    std::cout << "INDEX ARE (0-"<<(TwoDList.size()-1)<<")" << std::endl;
    auto values = DoubleInputHandler();
    i = values.first;
    j = values.second;

    double distance = TwoDList.at(i).Distance(TwoDList.at(j));
    std::cout << "THE DISTANCE BETWEEN POINTS AT INDEX " << i << " AND INDEX " << j << " IS: " << distance <<std::endl; 
}
void TwoDManager::Midpoint(){
    int i=0,j=0;
    std::cout << "INDEX ARE (0-"<<(TwoDList.size()-1)<<")" << std::endl;
    auto values = DoubleInputHandler();
    i = values.first;
    j = values.second;

    auto Mid = TwoDList.at(i).Midpoint(TwoDList.at(j));

    std::cout << "MIDPOINT BETWEEN POINTS AT INDEX " << i << " AND " << j << " IS: (x=" << Mid.first << " , y= "<<Mid.second<<')'<<std::endl;

}
void TwoDManager::PointManipulation(){
    int i=0;
    std::cout << "WHICH POINT WOULD YOU LIKE TO MANIPULATE AND GET A NEW MANIPULATED POINT?:\n";
    std::cout << "INDEX ARE (0-"<<(TwoDList.size()-1)<<")" << std::endl;
    i = SingleInputHandler();
    Point2D Point1 = TwoDList.at(i);

    std::string choice;

    do{
        std::cout << "2D-POINT MANIPULATION MENU!\n";
        std::cout << "PRESS 1 TO MULTIPLY A SCALAR TO A POINT!\n";
        std::cout << "PRESS 2 TO ADD A SCALAR TO A POINT!\n";
        std::cout << "PRESS 3 TO SUBTRACT A SCALAR FROM A POINT!\n";
        std::cout << "PRESS 4 TO DIVIDE A SCALAR FROM A  POINT!\n";
        std::cout << "PRESS 5 TO EQUATE(==) THE TWO POINTS!\n";
        std::cout << "PRESS '-1' TO EXIT THE POINT MANIPULATION MENU!\n";
        std::cin>>choice;

        if(choice == "1"){
            double x;
            std::cout << "PLEASE ENTER THE SCALAR MULTIPLE!:\n";
            std::cin >> x;
            // Point2D Point2 = Point1*x;
            TwoDList.push_back(Point1*x);
            std::cout << "NEW POINT ADDED TO INDEX!: " << TwoDList.size()-1<<std::endl;
        }
        else if(choice == "2"){
            double x;
            std::cout << "PLEASE ENTER THE SCALAR ADDITION!:\n";
            std::cin >> x;
            // Point2D Point2 = Point1+x;
            TwoDList.push_back( Point1+x);
            std::cout << "NEW POINT ADDED TO INDEX!: " << TwoDList.size()-1<<std::endl;
        }
        else if(choice == "3"){
            double x;
            std::cout << "PLEASE ENTER THE SCALAR SUBTRACTION!:\n";
            std::cin >> x;
            // Point2D Point2 = Point1-x;
            TwoDList.push_back(Point1-x);
            std::cout << "NEW POINT ADDED TO INDEX!: " << TwoDList.size()-1<<std::endl;
        }
        else if(choice == "4"){
            double x;
            std::cout << "PLEASE ENTER THE SCALAR DIVISOR!:\n";
            std::cin >> x;
            // Point2D Point2 = Point1/x;
            TwoDList.push_back(Point1/x);
            std::cout << "NEW POINT ADDED TO INDEX!: " << TwoDList.size()-1<<std::endl;
        }
        else if(choice == "5"){
            int j=0;
            j = SingleInputHandler();
            if(Point1==TwoDList[j]){
                std::cout << "THESE TWO POINTS ARE EQUAL!\n";
            }else{
                std::cout << "THESE TWO POINTS ARE NOT EQUAL!\n";
            }
        }else if(choice=="-1"){
            std::cout << "EXITING THE 2D-POINT MANIPULATION MENU!\n";
        }
        else{
            std::cout << "INVALID ENTRY! TRY AGAIN!\n";
        }
    }while(choice!="-1");
}
void TwoDManager::Graph(){
    int i;
    std::cout << "INDEX ARE (0-"<<(TwoDList.size()-1)<<")" << std::endl;
    i = SingleInputHandler();
    TwoDList[i].GraphPoint();
}
void TwoDManager::AddTwoDList(std::vector<Point2D> List){
    for(int i=0;i<List.size();i++){
        TwoDList.push_back(List.at(i));
    }
}
// ===================
// THREE DIMENSION MANAGER 
//  FUNCTION DEFINIIONS
// ===================
void ThreeDManager::AddPoint(){
    double a,b,c;

    std::cout << "PLEASE ENTER THE X COORDINATE OF 2D-POINT: ";
    a=PointInputHandler();
    std::cout << "PLEASE ENTER THE Y COORDINATE OF 2D-POINT: ";
    b=PointInputHandler();
    std::cout << "PLEASE ENTER THE Z COORDINATE OF THE 3D-POINT: ";
    c=PointInputHandler();

    Point3D Temp(a,b,c);
    ThreeDList.push_back(Temp);
    std::cout << "POINT SUCCESFULLY ADDED TO 3-D LIST!\n";
}
void ThreeDManager::DisplayPoint(){
    int i=0;

    std::cout << "INDEX ARE (0-" << (ThreeDList.size()-1) <<")\n";
    i=SingleInputHandler();
    std::cout << "3D POINT AT INDEX: " << i << "=>" <<std::endl;
    ThreeDList[i].Display();
}
void ThreeDManager::ListAllPoints(){
    int max = ThreeDList.size();

    for(int i=0;i<max;i++){
        std::cout << "INDEX=>" << i << std::endl;
        ThreeDList[i].Display();
    }
}
void ThreeDManager::RemovePoint(){
    int i=0;

    std::cout << "INDEX ARE (0-" << (ThreeDList.size()-1) << ")\n";
    i=SingleInputHandler();

    ThreeDList.erase(ThreeDList.begin()+i);
    std::cout << "3D POINT AT INDEX " << i << "REMOVED SUCCESSFULLY!\n";
}
void ThreeDManager::DistanceBetweenPoints(){
    int i=0,j=0;
    std::cout << "INDEX ARE (0-" << (ThreeDList.size()-1) <<")\n";
    auto temp = DoubleInputHandler();
    i = temp.first;
    j = temp.second;
    double D = ThreeDList.at(i).Distance(ThreeDList.at(j));
    std::cout << "THE DISTANCE BETWEEN POINTS AT INDEX " << i << " AND INDEX " << j << "IS: " << D <<std::endl;
}
void ThreeDManager::Midpoint(){
    int i=0,j=0;
    std::cout << "INDEX ARE (0-" << (ThreeDList.size()-1) << ")\n";

    auto temp = DoubleInputHandler();
    i = temp.first;
    j = temp.second;

    auto [x,y,z]= ThreeDList.at(i).Midpoint(ThreeDList.at(j));
    std::cout << "THE MIDPOINTS BETWEEN POINTS AT INDEX " << i << " AND INDEX " << j << "IS=>\n" ;
    std::cout << "(x=" << x << ",y=" << y << "z=" << z << ")\n";
}
void ThreeDManager::PointManipulation(){
    int i=0;
    std::cout << "WHICH POINT WOULD YOU LIKE TO MANIPULATE AND GET A NEW MANIPULATED POINT?:\n";
    std::cout << "INDEX ARE (0-"<<(ThreeDList.size()-1)<<")" << std::endl;
    i = SingleInputHandler();
    Point3D Point1 = ThreeDList.at(i);

    std::string choice;

    do{
        std::cout << "3D-POINT MANIPULATION MENU!\n";
        std::cout << "PRESS 1 TO MULTIPLY A SCALAR TO A POINT!\n";
        std::cout << "PRESS 2 TO ADD A SCALAR TO A POINT!\n";
        std::cout << "PRESS 3 TO SUBTRACT A SCALAR FROM A POINT!\n";
        std::cout << "PRESS 4 TO DIVIDE A SCALAR FROM A  POINT!\n";
        std::cout << "PRESS 5 TO EQUATE(==) THE TWO POINTS!\n";
        std::cout << "PRESS '-1' TO EXIT THE POINT MANIPULATION MENU!\n";
        std::cin>>choice;

        if(choice=="1"){
            double x;
            std::cout << "PLEASE INPUT THE SCALAR MULTIPLE!:\n";
            std::cin >> x;
            ThreeDList.push_back(Point1*x);
        }else if(choice=="2"){
            double x;
            std::cout << "PLEASE INPUT THE SCALAR ADDITION!:\n";
            std::cin >> x;
            ThreeDList.push_back(Point1+x);
            std::cout << "NEW POINT ADDED TO INDEX!: " << (ThreeDList.size()-1) << std::endl;
        }else if(choice=="3"){
            double x;
            std::cout << "PLEASE INPUT THE SCALAR SUBTRACTION!:\n";
            std::cin >> x;
            ThreeDList.push_back(Point1-x);
            std::cout << "NEW POINT ADDED TO INDEX!: " << (ThreeDList.size()-1) << std::endl;
        }else if(choice=="4"){
            double x;
            std::cout << "PLEASE ADD THE SCALAR DIVISOR!\n";
            std::cin >> x;
            ThreeDList.push_back(Point1/x);
            std::cout << "NEW POINT ADDED TO INDEX!: " << (ThreeDList.size()-1) << std::endl;
        }else if(choice=="5"){
            int j=0;
            j = SingleInputHandler();
            if(Point1==ThreeDList.at(j)){
                std::cout << "THESE TWO POINTS ARE EQUAL!\n";
            }else{
                std::cout << "THESE TWO POINTS ARE NOT EQUAL!\n";
            }
        }else if(choice=="-1"){
            std::cout << "EXITING THE 3D-POINT MANIPULATION MENU!\n";
        }
    }while(choice!="-1");

}
void ThreeDManager::AddThreeDList(std::vector<Point3D> List){
    for(int i=0;i<List.size();i++){
        ThreeDList.push_back(List.at(i));
    }
}
// ===================
//    FILE HANDLER 
// FUNCTION DEFINIIONS
// ===================

void FileHandler::Set2DPath(std::string path){
    TwoDFilepath=path;
}
void FileHandler::Set3DPath(std::string path){
    ThreeDFilepath=path;
}
void FileHandler::InputToTwoDFile(const TwoDManager &obj){
    std::ofstream TwoDFile(TwoDFilepath);
    if(TwoDFile.is_open()){
        for(int i=0;i<obj.TwoDList.size();i++){
            Point2D Point = obj.TwoDList.at(i);
            TwoDFile << Point.x << "," << Point.y<<std::endl;
        }
        TwoDFile.close();
    }else{
        std::cout << "INVALID FILE PATH!\n";
    }

}
std::vector<Point2D> FileHandler::ReadFromTwoDFile(){
    std::vector<Point2D> List;
    std::ifstream TwoDFile(TwoDFilepath);
    std::string line;
    if(TwoDFile.is_open()){
        while(std::getline(TwoDFile,line)){
            int index = line.find(',');
            std::string tempx,tempy;
            for(int i=0;i<index;i++){
                tempx+=line[i];
            }
            for(int j=index+1;j<line.length();j++){
                tempy+=line[j];
            }
            List.push_back(Point2D(std::stod(tempx),std::stod(tempy)));
        }
        TwoDFile.close();
    }else{
        return {};
    }
    return List;
}
void FileHandler::InputToThreeDFile(const ThreeDManager &obj){
    std::ofstream ThreeDFile(ThreeDFilepath);

    if(ThreeDFile.is_open()){
        for(int i=0;i<obj.ThreeDList.size();i++){
            Point3D Point = obj.ThreeDList.at(i);
            ThreeDFile << Point.x << ',' << Point.y << ',' << Point.z << std::endl;
        }
        ThreeDFile.close();
    }else{
        std::cout << "INVALID FILE PATH!\n";
    }
}
std::vector<Point3D> FileHandler::ReadFromThreeDFile(){
    std::vector<Point3D> List;
    std::ifstream ThreeDFile(ThreeDFilepath);
    std::string line;
    if(ThreeDFile.is_open()){
        while(std::getline(ThreeDFile,line)){
            int index = line.find(',');
            int index1 = line.find(',',index+1);
            std::string tempx,tempy,tempz;
            for(int i=0;i<index;i++){
                tempx+=line[i];
            }
            for(int j=index+1;j<index1;j++){
                tempy+=line[j];
            }
            for(int k=index1+1;k<line.length();k++){
                tempz+=line[k];
            }
            List.push_back(Point3D(std::stod(tempx),std::stod(tempy),std::stod(tempz)));
        }
        ThreeDFile.close();
    }else{
        return {};
    }
    return List;
}