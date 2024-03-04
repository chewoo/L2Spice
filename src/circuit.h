#ifndef CIRCUIT_H
#define CIRCUIT_H
#include "resistor.h"
#include "inductor.h"
#include "capacitor.h"
#include "ground.h"
#include <matrix.h>
#include <math.h>
#include "voltage_source.h"
#include "current_source.h"
#include <current_control_current_source.h>
#include <current_control_voltage_source.h>
#include <voltage_control_current_source.h>
#include <voltage_control_voltage_source.h>
#include "diode.h"
#include <linenodeitem.h>
enum circuit_state{
    ok = 0,
    idle ,
    no_component,
    no_ground,
    no_solution,

};
struct circuit_Matrixsystem{
    Matrix* A;
    Matrix* b;
    Matrix ini_A;

    bool ini = false;
    void clear(){
        if(ini==true){
            delete A;
            delete b;
            ini_A.setall(0);
            ini = false;
        }
    }
};
class Circuit
{
    private:
        QVector<Component *> allComponent;
        QVector<Resistor *> allResistor;
        QVector<Inductor *> allInductor;
        QVector<Capacitor *> allCapacitor;
        QVector<voltage_source* >allVoltage_source;
        QVector<current_source* >allCurrent_source;
        QVector<Current_control_current_source*>allCCCS;
        QVector<Current_control_voltage_source*>allCCVS;
        QVector<Voltage_control_current_source*>allVCCS;
        QVector<Voltage_control_voltage_source*>allVCVS;
        QVector<Diode*>allDiode;
        QVector<LineNodeitem*> allLine;
        QVector<Ground* > allGround;
        QVector<int> nowSelectedItem;
        //QVector<Matrix> solutions;
        QVector< QPair<Matrix,double> > solutions; // ans, time
        int total_numofNode;//include zero(ground)
        QVector<QPair<int,int>> initial_condition;

        circuit_Matrixsystem sys;
        int state;
        Matrix get_jacobian(Matrix last_state,double timestep);
    public:

        Circuit();
        QVector<Component *> getAllComponent();
        QVector<Ground* > getAllground();
        QVector<int> getNowSelectedItem();
        QVector<LineNodeitem *> getAllLine();
        const QVector< QPair<Matrix,double> >& get_solutions();
        void setNowSelectedItem(int index);
        void updatedelete();
        void Input();
        void analysis_circuit_connection();
        void ini_sys();
        Matrix update_sys(const Matrix& last_state,double timestep,double current_time); // when analysis
        void analysis(double t,double maxtimestep  = -1);
        Matrix dc_analysis();
        double calculate_maxtimestep();
        void update_A_b(Matrix &A,Matrix &b,Matrix last_state,double timestep,double current_time);
        //QVector<Matrix> analysis_circuit_timeinterval(double t);
        //Matrix analysis_circuit(double t,double timestep);
        void sort_the_allcomponent();
        void push_backComponent(Component *);
        void push_backGround(Ground*);
        void push_backLine(LineNodeitem *);
        void deleteComponent(int index);
        void deleteAllComponent();
        void resetAllNodeIndex();
        void find_initial_condition();
        int get_circuit_state();
        int getDependantNode(QString a);
        Component* getDependantBranch(QString a);
        ~Circuit();
};

#endif // CIRCUIT_H
