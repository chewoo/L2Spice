#include "circuit.h"
#include <QStack>
#include <QList>
Circuit::Circuit()
{
    nowSelectedItem.clear();
    state = idle;
}

QVector<Component *> Circuit::getAllComponent()
{
    return allComponent;
}

QVector<int> Circuit::getNowSelectedItem()
{
    return nowSelectedItem;
}
QVector<Ground* > Circuit::getAllground()
{
    return allGround;
}
QVector<LineNodeitem *> Circuit::getAllLine()
{
    return allLine;
}
void Circuit::setNowSelectedItem(int index)
{

}
void Circuit::updatedelete()
{
    for(int i=0;i<allComponent.size();i++){
        if(allComponent[i]->getDelete()){
            allComponent[i]->Delete();
            delete allComponent[i];
            allComponent.erase(allComponent.begin()+i);
            i--;
        }
    }
    for(int i=0;i<allGround.size();i++){
        if(allGround[i]->getDelete()){
            delete allGround[i];
            allGround.erase(allGround.begin()+i);
            i--;
        }
    }
    for(int i=0;i<allLine.size();i++){
        if(allLine[i]->getDelete()){
            delete allLine[i];
            allLine.erase(allLine.begin()+i);
            i--;
        }
    }
}
void Circuit::Input()
{
    for(int i=0;i<allComponent.size();i++){
        if(allComponent[i]->getInput()){
            allComponent[i]->InputValue();

        }
    }
}
void Circuit::find_initial_condition()
{
    initial_condition.clear();
    for(int i=0;i<allLine.size();i++)
    {
        if(allLine[i]->getNode().first.getVoltage()!=0){
            initial_condition.push_back(qMakePair(allLine[i]->getNodeindex(),allLine[i]->getNode().first.getVoltage()));
        }
    }
}
void Circuit::analysis_circuit_connection()
{
    resetAllNodeIndex();
    if(allComponent.size()==0){
        state = no_component;
        qDebug()<<"There is no component";
        return;
    }else if(allGround.size() == 0){
        state = no_ground;
        qDebug()<<"no ground :(";
        return;
    }


    int node_num = 1;
    QStack<Node*> ground_stack;
    QStack<Node*> component_stack;
    for(int i=0;i<allGround.size();i++){
        allGround[i]->setNodeIndex(0);
        ground_stack.push(&allGround[i]->getNode());
    }
    while(ground_stack.size())
    {
        Node* current_ground = ground_stack.top();
        ground_stack.pop();

        for(int i=0;i<allComponent.size();i++){
            QVector<Node*> push_node = allComponent[i]->getNodes();
            for(int j=0;j<push_node.size();j++)
                if(current_ground->getPosition()==push_node[j]->getPosition()){
                    if(push_node[j]->getNodeIndex()==-1){
                        push_node[j]->setNodeIndex(0);
                    }
                    for(int l = 0;l<push_node.size();l++){
                        if(!component_stack.contains(push_node[l]) && push_node[l]->getNodeIndex() == -1)
                            component_stack.push(push_node[l]);
                    }
                }
        }

        QStack<LineNodeitem*> line_stack;

        for(int i=0;i<allLine.size();i++){
            if(allLine[i]->on_the_line(*current_ground)&&allLine[i]->getNodeindex()==-1){
                allLine[i]->setNodeindex(0);
                line_stack.push(allLine[i]);
            }
        }

        QList<LineNodeitem*> working_line;

        while(line_stack.size()){
            LineNodeitem* current_line = line_stack.top();
            line_stack.pop();
            if(!working_line.contains(current_line))
                working_line.append(current_line);
            for(int i=0;i<allLine.size();i++){
                if((current_line->line_and_line_connect(*allLine[i])||allLine[i]->line_and_line_connect(*current_line)) && allLine[i]->getNodeindex() == -1){
                    allLine[i]->setNodeindex(0);
                    line_stack.push(allLine[i]);
                }
            }
        }

        //qDebug()<<"asdasdadasd";
        for(int i=0;i<working_line.size();i++){
            for(int j=0;j<allComponent.size();j++){
                QVector<Node*> working_node = allComponent[j]->getNodes();
                for(int k=0;k<working_node.size();k++){
                    if(working_line[i]->on_the_line(*working_node[k])&&working_node[k]->getNodeIndex()==-1){
                        working_node[k]->setNodeIndex(0);
                        //qDebug()<<"setindex";
                        for(int l = 0;l<working_node.size();l++){
                            if(!component_stack.contains(working_node[l])&&working_node[l]->getNodeIndex()==-1)
                                component_stack.push(working_node[l]);
                        }
                    }
                }
            }
        }
    }

    while(component_stack.size())
    {
        Node* current_component = component_stack.top();
        component_stack.pop();
        if(current_component->getNodeIndex()!=-1)
        {
            continue;
        }else{
            current_component->setNodeIndex(node_num);
            node_num++;
        }

        for(int i=0;i<allComponent.size();i++){
            QVector<Node*> push_node = allComponent[i]->getNodes();
            for(int j=0;j<push_node.size();j++)
                if(current_component->getPosition()==push_node[j]->getPosition()){
                    if(push_node[j]->getNodeIndex()==-1){
                        push_node[j]->setNodeIndex(current_component->getNodeIndex());
                    }
                    for(int l = 0;l<push_node.size();l++){
                        if(!component_stack.contains(push_node[l]) && push_node[l]->getNodeIndex() == -1)
                            component_stack.push(push_node[l]);
                    }
                }
        }

        QStack<LineNodeitem*> line_stack;

        for(int i=0;i<allLine.size();i++){
            if(allLine[i]->on_the_line(*current_component)&&allLine[i]->getNodeindex()==-1){
                allLine[i]->setNodeindex(current_component->getNodeIndex());
                line_stack.push(allLine[i]);
            }
        }

        QList<LineNodeitem*> working_line;

        while(line_stack.size()){
            LineNodeitem* current_line = line_stack.top();
            line_stack.pop();
            if(!working_line.contains(current_line))
                working_line.append(current_line);
            for(int i=0;i<allLine.size();i++){
                if((current_line->line_and_line_connect(*allLine[i])||allLine[i]->line_and_line_connect(*current_line)) && allLine[i]->getNodeindex() == -1){
                    allLine[i]->setNodeindex(current_line->getNodeindex());
                    line_stack.push(allLine[i]);
                }
            }
        }
        for(int i=0;i<working_line.size();i++){
            for(int j=0;j<allComponent.size();j++){
                QVector<Node*> working_node = allComponent[j]->getNodes();
                for(int k=0;k<working_node.size();k++){
                    if(working_line[i]->on_the_line(*working_node[k])&&working_node[k]->getNodeIndex()==-1){
                        working_node[k]->setNodeIndex(working_line[i]->getNodeindex());
                        //qDebug()<<"setindex";
                        for(int l = 0;l<working_node.size();l++){
                            if(!component_stack.contains(working_node[l])&&working_node[l]->getNodeIndex()==-1)
                                component_stack.push(working_node[l]);
                        }
                    }
                }
            }
        }
    }


    for(int i=0;i<allComponent.size();i++){
        qDebug()<<allComponent[i]->getname()<<" "<<allComponent[i]->getNodes()[0]->getNodeIndex()<<" "<<allComponent[i]->getNodes()[1]->getNodeIndex();
    }
    state = ok;
    total_numofNode = node_num;
    //qDebug()<<total_numofNode;
}

void Circuit::ini_sys()
{
    solutions.clear();
    sys.clear();
    if(state!=ok){
        qDebug()<<"There is something wrong @@";
        return;
    }else if(sys.ini == true){
        qDebug()<<"Already initialized";
        return;
    }

    int num_of_unknown = total_numofNode-1;//without ground
    num_of_unknown += allVoltage_source.size();
    num_of_unknown += allCapacitor.size();
    num_of_unknown += allInductor.size();
    num_of_unknown += allVCVS.size();
    num_of_unknown += allCCVS.size();
    sys.A = new Matrix(num_of_unknown,num_of_unknown,0);
    sys.b = new Matrix(num_of_unknown,1,0);
    sys.ini = true;

    //resistor stamps

    int matrix_offset=0;
    for(int i=0;i<allResistor.size();i++){
        int node1 = allResistor[i]->getNodeindex1()-1;
        int node2 = allResistor[i]->getNodeindex2()-1;
        double conductance = 1/allResistor[i]->get_resistance();
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            sys.A->add_ij(node2,node2,conductance);
        }else if(node2<0){
            sys.A->add_ij(node1,node1,conductance);
        }else{
            sys.A->add_ij(node1,node1,conductance);
            sys.A->add_ij(node2,node2,conductance);
            sys.A->add_ij(node1,node2,-conductance);
            sys.A->add_ij(node2,node1,-conductance);
        }
    }
    /*
    //current_source stamps
    for(int i=0;i<allCurrent_source.size();i++){
        int node1 = allCurrent_source[i]->getNodeindex1()-1; // 1->2
        int node2 = allCurrent_source[i]->getNodeindex2()-1;
        double current = allCurrent_source[i]->get_current(0);
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            sys.b->add_ij(node2,0,current);
        }else if(node2<0){
            sys.b->add_ij(node1,0,current);
        }else{
            sys.b->add_ij(node1,0,current);
            sys.b->add_ij(node2,0,-current);
        }
    }
    */
    //voltage_source stamps
    matrix_offset = total_numofNode-1;
    for(int i=0;i<allVoltage_source.size();i++){
        int node1 = allVoltage_source[i]->getNodeindex1()-1; //-
        int node2 = allVoltage_source[i]->getNodeindex2()-1; //+
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            sys.A->add_ij(matrix_offset+i,node2,1);
            sys.A->add_ij(node2,matrix_offset+i,1);
        }else if(node2<0){
            sys.A->add_ij(matrix_offset+i,node2,1);
            sys.A->add_ij(node2,matrix_offset+i,1);
        }else{
            sys.A->add_ij(matrix_offset+i,node2,1);
            sys.A->add_ij(node2,matrix_offset+i,1);
            sys.A->add_ij(matrix_offset+i,node1,-1);
            sys.A->add_ij(node1,matrix_offset+i,-1);
        }
    }
     sys.ini_A = *sys.A;
    //capacitor stamps
    matrix_offset = total_numofNode-1+allVoltage_source.size();
    for(int i=0;i<allCapacitor.size();i++){
        int node1 = allCapacitor[i]->getNodeindex1()-1;//assume current 1 -> 2
        int node2 = allCapacitor[i]->getNodeindex2()-1;
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){

            sys.ini_A.set_ij(matrix_offset+i,matrix_offset+i,-1);
            sys.ini_A.add_ij(node2,matrix_offset+i,-1);

        }else if(node2<0){

            sys.ini_A.set_ij(matrix_offset+i,matrix_offset+i,-1);
            sys.ini_A.add_ij(node1,matrix_offset+i,1);

        }else{

            sys.ini_A.set_ij(matrix_offset+i,matrix_offset+i,-1);
            sys.ini_A.add_ij(node1,matrix_offset+i,1);
            sys.ini_A.add_ij(node2,matrix_offset+i,-1);

        }
    }
    //inductor stamps
    matrix_offset = total_numofNode-1+allVoltage_source.size()+allCapacitor.size();
    for(int i=0;i<allInductor.size();i++){
        int node1 = allInductor[i]->getNodeindex1()-1;
        int node2 = allInductor[i]->getNodeindex2()-1;
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){

            sys.ini_A.add_ij(matrix_offset+i,node2,1);
            sys.ini_A.add_ij(node2,matrix_offset+i,1);

        }else if(node2<0){

            sys.ini_A.add_ij(matrix_offset+i,node1,-1);
            sys.ini_A.add_ij(node1,matrix_offset+i,-1);

        }else{

            sys.ini_A.add_ij(matrix_offset+i,node1,-1);
            sys.ini_A.add_ij(matrix_offset+i,node2,1);
            sys.ini_A.add_ij(node1,matrix_offset+i,-1);
            sys.ini_A.add_ij(node2,matrix_offset+i,1);
        }
    }
    //VCCS stamps
    for(int i=0;i<allVCCS.size();i++){
        int node1 = allVCCS[i]->getNodeindex1()-1;//1 --> 2
        int node2 = allVCCS[i]->getNodeindex2()-1;
        int s_node1 = getDependantNode(allVCCS[i]->getDependantNode1())-1;
        int s_node2 = getDependantNode(allVCCS[i]->getDependantNode2())-1;
        double G = allVCCS[i]->getCoefficient();
        if(node1<0&&node2<0){
            continue;
        }else if(s_node1<0&&s_node2<0){
            continue;
        }else{
            if(node1>=0&&s_node1>=0)
                sys.ini_A.add_ij(node1,s_node1,G);
            if(node1>=0&&s_node2>=0)
                sys.ini_A.add_ij(node1,s_node2,-G);
            if(node2>=0&&s_node1>=0)
                sys.ini_A.add_ij(node2,s_node1,-G);
            if(node2>=0&&s_node2>=0)
                sys.ini_A.add_ij(node2,s_node2,G);
        }
    }
    //VCVS stamps
    matrix_offset += allInductor.size();
    for(int i=0;i<allVCVS.size();i++){
        int node1 = allVCVS[i]->getNodeindex1()-1;//-
        int node2 = allVCVS[i]->getNodeindex2()-1;//+
        int s_node1 = getDependantNode(allVCVS[i]->getDependantNode1())-1;
        int s_node2 = getDependantNode(allVCVS[i]->getDependantNode2())-1;
        double A = allVCVS[i]->getCoefficient();
        if(node1<0&&node2<0){
            continue;
        }else if(s_node1<0&&s_node2<0){
            continue;
        }else if(node1<0){
            if(s_node1<0){
                sys.ini_A.add_ij(matrix_offset+i,node2,1);
                sys.ini_A.add_ij(matrix_offset+i,s_node2,A);
                sys.ini_A.add_ij(node2,matrix_offset+i,1);
            }else if(s_node2<0){
                sys.ini_A.add_ij(matrix_offset+i,node2,1);
                sys.ini_A.add_ij(matrix_offset+i,s_node1,-A);
                sys.ini_A.add_ij(node2,matrix_offset+i,1);
            }else{
                sys.ini_A.add_ij(matrix_offset+i,node2,1);
                sys.ini_A.add_ij(matrix_offset+i,s_node2,A);
                sys.ini_A.add_ij(matrix_offset+i,s_node1,-A);
                sys.ini_A.add_ij(node2,matrix_offset+i,1);
            }
        }else if(node2<0){
            if(s_node1<0){
                sys.ini_A.add_ij(matrix_offset+i,node1,-1);
                sys.ini_A.add_ij(matrix_offset+i,s_node2,A);
                sys.ini_A.add_ij(node1,matrix_offset+i,-1);
            }else if(s_node2<0){
                sys.ini_A.add_ij(matrix_offset+i,node1,-1);
                sys.ini_A.add_ij(matrix_offset+i,s_node1,-A);
                sys.ini_A.add_ij(node1,matrix_offset+i,-1);
            }else{
                sys.ini_A.add_ij(matrix_offset+i,node1,-1);
                sys.ini_A.add_ij(matrix_offset+i,s_node2,A);
                sys.ini_A.add_ij(matrix_offset+i,s_node1,-A);
                sys.ini_A.add_ij(node1,matrix_offset+i,-1);
            }
        }else{
            if(s_node1<0){
                sys.ini_A.add_ij(node2,matrix_offset+i,1);
                sys.ini_A.add_ij(matrix_offset+i,node2,1);
                sys.ini_A.add_ij(matrix_offset+i,node1,-1);
                sys.ini_A.add_ij(node1,matrix_offset+i,-1);
                sys.ini_A.add_ij(matrix_offset+i,s_node2,A);
            }else if(s_node2<0){
                sys.ini_A.add_ij(node2,matrix_offset+i,1);
                sys.ini_A.add_ij(matrix_offset+i,node2,1);
                sys.ini_A.add_ij(matrix_offset+i,node1,-1);
                sys.ini_A.add_ij(node1,matrix_offset+i,-1);
                sys.ini_A.add_ij(matrix_offset+i,s_node1,-A);
            }else{
                sys.ini_A.add_ij(node2,matrix_offset+i,1);
                sys.ini_A.add_ij(matrix_offset+i,node2,1);
                sys.ini_A.add_ij(matrix_offset+i,node1,-1);
                sys.ini_A.add_ij(node1,matrix_offset+i,-1);
                sys.ini_A.add_ij(matrix_offset+i,s_node2,A);
                sys.ini_A.add_ij(matrix_offset+i,s_node1,-A);
            }
        }
    }
    //CCCS stamps
    int matrix_offsetCCCS = total_numofNode-1;
    for(int i=0;i<allCCCS.size();i++){
        int node1 = allCCCS[i]->getNodeindex1()-1;//1 ---> 2
        int node2 = allCCCS[i]->getNodeindex2()-1;
        int vs_num=0;
        double A = allCCCS[i]->getCoefficient();
        Component* s_node = getDependantBranch(allCCCS[i]->getDependantBranchName());
        voltage_source* vs = dynamic_cast<voltage_source*>(s_node);
        if(!vs){
            qDebug()<<"Wrong usage";
        }else{
            vs_num = vs->get_num();
        }
        if(node1>=0)
            sys.ini_A.add_ij(node1,matrix_offsetCCCS+vs_num,A);
        if(node2>=0)
            sys.ini_A.add_ij(node2,matrix_offsetCCCS+vs_num,-A);
    }
    matrix_offset += allVCVS.size();
    int matrix_offsetCCVS = total_numofNode-1;
    for(int i=0;i<allCCVS.size();i++){
        int node1 = allCCVS[i]->getNodeindex1()-1;//-
        int node2 = allCCVS[i]->getNodeindex2()-1;//+
        int vs_num=0;
        double A = allCCVS[i]->getCoefficient();
        Component* s_node = getDependantBranch(allCCVS[i]->getDependantBranchName());
        voltage_source* vs = dynamic_cast<voltage_source*>(s_node);
        if(!vs){
            qDebug()<<"Wrong usage";
        }else{
            vs_num = vs->get_num();
        }
        if(node1>=0){
            sys.ini_A.add_ij(matrix_offset+i,node1,-1);
            sys.ini_A.add_ij(node1,matrix_offset+i,-1);
        }
        if(node2>=0){
            sys.ini_A.add_ij(matrix_offset+i,node2,1);
            sys.ini_A.add_ij(node2,matrix_offset+i,1);
        }
        sys.ini_A.add_ij(matrix_offset+i,matrix_offsetCCVS+vs_num,-A);
    }

}
int dick = 1;
Matrix Circuit::update_sys(const Matrix& last_state,double timestep,double current_time)
{
    if(sys.ini == false){
        qDebug()<<"non initialization";
        return Matrix();
    }
    int matrix_offset=0;
    (*sys.A) = sys.ini_A;

    sys.b->setall(0);
    //current_source stamps
    for(int i=0;i<allCurrent_source.size();i++){
        int node1 = allCurrent_source[i]->getNodeindex1()-1; // 1->2
        int node2 = allCurrent_source[i]->getNodeindex2()-1;
        double current = allCurrent_source[i]->get_current(current_time);
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            sys.b->add_ij(node2,0,current);
        }else if(node2<0){
            sys.b->add_ij(node1,0,current);
        }else{
            sys.b->add_ij(node1,0,current);
            sys.b->add_ij(node2,0,-current);
        }
    }
    //voltage_source stamps
    matrix_offset = total_numofNode-1;
    for(int i=0;i<allVoltage_source.size();i++){
        int node1 = allVoltage_source[i]->getNodeindex1()-1; //-
        int node2 = allVoltage_source[i]->getNodeindex2()-1; //+
        double voltage = allVoltage_source[i]->get_voltage(current_time);
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            sys.b->add_ij(matrix_offset+i,0,voltage);
        }else if(node2<0){
            sys.b->add_ij(matrix_offset+i,0,-voltage);
        }else{
            sys.b->add_ij(matrix_offset+i,0,voltage);
        }
    }
    //capacitor stamps
    matrix_offset = total_numofNode-1+allVoltage_source.size();
    for(int i=0;i<allCapacitor.size();i++){
        int node1 = allCapacitor[i]->getNodeindex1()-1;
        int node2 = allCapacitor[i]->getNodeindex2()-1;
        double capacitance = allCapacitor[i]->get_capacitance();
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            sys.A->add_ij(matrix_offset+i,node2,-capacitance/timestep);
            sys.b->add_ij(matrix_offset+i,0, capacitance * (-last_state(node2,0)) /timestep);
        }else if(node2<0){
            sys.A->add_ij(matrix_offset+i,node1,capacitance/timestep);
            sys.b->add_ij(matrix_offset+i,0,capacitance * (last_state(node1,0)) /timestep);
        }else{
            sys.A->add_ij(matrix_offset+i,node1,capacitance/timestep);
            sys.A->add_ij(matrix_offset+i,node2,-capacitance/timestep);
            sys.b->add_ij(matrix_offset+i,0,capacitance*(last_state(node1,0)-last_state(node2,0))/timestep);
        }


    }
    //inductor stamps
    matrix_offset = total_numofNode-1+allVoltage_source.size()+allCapacitor.size();
    for(int i=0;i<allInductor.size();i++){
        int node1 = allInductor[i]->getNodeindex1()-1;
        int node2 = allInductor[i]->getNodeindex2()-1;
        double inductance = allInductor[i]->getInductance();
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            sys.A->add_ij(matrix_offset+i,matrix_offset+i,-inductance/timestep);
            sys.b->add_ij(matrix_offset+i,0,-inductance*last_state(matrix_offset+i,0)/timestep);

        }else if(node2<0){
            sys.A->add_ij(matrix_offset+i,matrix_offset+i,-inductance/timestep);
            sys.b->add_ij(matrix_offset+i,0,-inductance*last_state(matrix_offset+i,0)/timestep);

        }else{
            sys.A->add_ij(matrix_offset+i,matrix_offset+i,-inductance/timestep);
            sys.b->add_ij(matrix_offset+i,0,-inductance*last_state(matrix_offset+i,0)/timestep);
        }
    }
    //qDebug()<<"diode enter";

    if(allDiode.size()==0){
        Matrix  ans = sys.A->solve_gauss_elimination(*sys.b);
        //sys.A->debug();
        //sys.b->debug();
        //ans.debug();
        return ans;
    }
    Matrix non_linear = *sys.b;
    non_linear.setall(0);
    QVector<QPair<int,int>> diodes_v;
    for(int i=0;i<allDiode.size();i++){
        int node1 = allDiode[i]->getNodeindex1()-1; // 1 --|>-- 2
        int node2 = allDiode[i]->getNodeindex2()-1;

        diodes_v.push_back(qMakePair(node1,node2));
    }
    double diff = 100;
    double accuracy = 1e-1;
    Matrix next_iter;
    Matrix curr_iter = last_state;
    Matrix f;
    Matrix A = *sys.A;
    Matrix b = *sys.b;
    Matrix Jacobian;
    //NR iteration
    int count=0;
    while(diff>accuracy)
    {

        update_A_b(A,b,curr_iter,timestep,current_time);
        Jacobian = get_jacobian(curr_iter,timestep);
        //qDebug()<<"diode out";
        for(int i=0;i<allDiode.size();i++){
            int node1 = allDiode[i]->getNodeindex1()-1; // 1 --|>-- 2
            int node2 = allDiode[i]->getNodeindex2()-1;
            double Isat = allDiode[i]->get_Isat();
            double Vd = curr_iter(node1,0)-curr_iter(node2,0);
            if(Vd<=0)
                continue;
            double Id = Isat*(exp(40*Vd)-1);
            if(!isnormal(Id))
                continue;
            //double Io = (exp(40*Vd)-1) - G*Vd;
            if(node1<0&&node2<0){
                continue;
            }else if(node1<0){
                non_linear.add_ij(node2,0,-Id);
                //b.add_ij(node2,0,Io);

            }else if(node2<0){
                non_linear.add_ij(node1,0,Id);
                //b.add_ij(node1,0,-Io);
            }else{
                non_linear.add_ij(node1,0,Id);
                non_linear.add_ij(node2,0,-Id);
               // b.add_ij(node1,0,-Io);
               // b.add_ij(node2,0,Io);
            }
        }
        f = A*curr_iter+non_linear-(b);
        //f.debug();

        next_iter = Jacobian.solve_gauss_elimination(Jacobian*curr_iter-f);

        diff = Matrix::calculate_maxVdifference(curr_iter,next_iter);
        if(diff == -1)
            dick = 0;

        //curr_iter.debug();
        //next_iter.debug();
        curr_iter = next_iter;

        //qDebug()<<diff;
    }

    return curr_iter;

}

void Circuit::analysis(double t,double maxtimestep)
{

    double current_time = 0;
    double min_timestep = t/200000;
    double max_timestep;
    if(maxtimestep == -1)
        max_timestep = calculate_maxtimestep();
    else
        max_timestep = maxtimestep;
    qDebug()<<"max";
    qDebug()<<max_timestep;
    double accuracy = 1e-3;
    double timestep = (min_timestep);
    //initial state dc analysis
    Matrix last_state = dc_analysis();
    ini_sys();
    solutions.push_back(qMakePair(last_state,0));
    //total_numofNode-1;

    while(current_time<=t){

        //double diff = 0;

        Matrix x_step;
        Matrix x_halfstep;
        Matrix x_twohalfstep;
        Matrix x_now = solutions.back().first;
        Matrix x_better;

        x_step = update_sys(x_now,timestep,current_time);
        x_halfstep = update_sys(x_now,timestep/2,current_time);
        x_twohalfstep = update_sys(x_halfstep,timestep/2,current_time+timestep/2);

        double diff = Matrix::calculate_maxVdifference(x_step,x_twohalfstep);
        //qDebug()<<timestep;

        if(diff>0){
           timestep = sqrt(accuracy/diff)*timestep;
        }else if(diff==0){
            timestep = 1000*timestep;
        }
        //qDebug()<<diff<<" "<<timestep;
        if(timestep<min_timestep)
            timestep = min_timestep;
        if(timestep>max_timestep)
            timestep = max_timestep;
        //timestep = t/10000;
        x_better = update_sys(x_now,timestep,current_time);

        current_time+=timestep;
        solutions.push_back(qMakePair(x_better,current_time));

        //timestep = t/10000;

    }
}
double Circuit::calculate_maxtimestep()
{
    double ans = INT32_MAX;
    for(int i=0;i<allVoltage_source.size();i++){
        if(!allVoltage_source[i]->isDCsource()){
            qDebug()<<1/allVoltage_source[i]->getFrequency();
            ans = std::min(ans,1/allVoltage_source[i]->getFrequency());
        }
    }
    for(int i=0;i<allCurrent_source.size();i++){
        if(!allCurrent_source[i]->isDCsource()){
            ans = std::min(ans,1/allCurrent_source[i]->getFrequency());
        }
    }
    for(int i=0;i<allCapacitor.size();i++){
        for(int j=0;j<allInductor.size();j++){
            ans = std::min(ans,sqrt(allCapacitor[i]->get_capacitance()*allInductor[i]->getInductance())/(2*M_PI));
        }
    }
    return ans/10;
}
Matrix Circuit::dc_analysis()
{
    if(state!=ok){
        qDebug()<<"There is something wrong @@";
        return Matrix(1,1,0);
    }
    bool no_dc = true;
    int num_of_unknown = total_numofNode-1;//without ground
    num_of_unknown += allVoltage_source.size();
    num_of_unknown += allCapacitor.size();
    num_of_unknown += allInductor.size();
    num_of_unknown += allVCVS.size();
    num_of_unknown += allCCVS.size();

    Matrix A(num_of_unknown,num_of_unknown,0);
    Matrix b(num_of_unknown,1,0);
    Matrix last_state(num_of_unknown,1,0);
    //qDebug()<<"hello";
    for(int i=0;i<initial_condition.size();i++){
        if(initial_condition[i].first != 0)
            last_state.set_ij(initial_condition[i].first-1,0,initial_condition[i].second);
    }
    //Debug()<<"hello";
    //resistor stamps

    int matrix_offset=0;
    for(int i=0;i<allResistor.size();i++){
        int node1 = allResistor[i]->getNodeindex1()-1;
        int node2 = allResistor[i]->getNodeindex2()-1;
        double conductance = 1/allResistor[i]->get_resistance();
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            A.add_ij(node2,node2,conductance);
        }else if(node2<0){
            A.add_ij(node1,node1,conductance);
        }else{
            //qDebug()<<node1<<" "<<node2;
            A.add_ij(node1,node1,conductance);
            A.add_ij(node2,node2,conductance);
            A.add_ij(node1,node2,-conductance);
            A.add_ij(node2,node1,-conductance);
        }

    }
    //current_source stamps
    for(int i=0;i<allCurrent_source.size();i++){
        if(!allCurrent_source[i]->isDCsource())
            continue;
        no_dc = false;
        int node1 = allCurrent_source[i]->getNodeindex1()-1; // 1->2
        int node2 = allCurrent_source[i]->getNodeindex2()-1;
        double current = allCurrent_source[i]->get_current(0);
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            b.add_ij(node2,0,current);
        }else if(node2<0){
            b.add_ij(node1,0,current);
        }else{
            b.add_ij(node1,0,current);
            b.add_ij(node2,0,-current);
        }
    }
    //voltage_source stamps
    matrix_offset = total_numofNode-1;
    for(int i=0;i<allVoltage_source.size();i++){
        int node1 = allVoltage_source[i]->getNodeindex1()-1; //-
        int node2 = allVoltage_source[i]->getNodeindex2()-1; //+
        double voltage = allVoltage_source[i]->get_voltage(0);
        if(!allVoltage_source[i]->isDCsource())
            voltage = 0;
        else
            no_dc = false;
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            A.add_ij(matrix_offset+i,node2,1);
            A.add_ij(node2,matrix_offset+i,1);
            b.add_ij(matrix_offset+i,0,voltage);
        }else if(node2<0){
            A.add_ij(matrix_offset+i,node2,1);
            A.add_ij(node2,matrix_offset+i,1);
            b.add_ij(matrix_offset+i,0,-voltage);
        }else{
            A.add_ij(matrix_offset+i,node2,1);
            A.add_ij(node2,matrix_offset+i,1);
            A.add_ij(matrix_offset+i,node1,-1);
            A.add_ij(node1,matrix_offset+i,-1);
            b.add_ij(matrix_offset+i,0,voltage);
        }
    }

    for(int i=0;i<initial_condition.size();i++){
        if(initial_condition[i].first != 0)
            last_state.set_ij(initial_condition[i].first-1,0,initial_condition[i].second);
    }
    if(no_dc){
        return last_state;
    }
    //capacitor stamps
    matrix_offset = total_numofNode-1+allVoltage_source.size();
    for(int i=0;i<allCapacitor.size();i++){
        int node1 = allCapacitor[i]->getNodeindex1()-1;
        int node2 = allCapacitor[i]->getNodeindex2()-1;
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            A.set_ij(matrix_offset+i,matrix_offset+i,-1);
            A.add_ij(node2,matrix_offset+i,-1);
        }else if(node2<0){
            A.set_ij(matrix_offset+i,matrix_offset+i,-1);
            A.add_ij(node1,matrix_offset+i,1);
        }else{
            A.set_ij(matrix_offset+i,matrix_offset+i,-1);
            A.add_ij(node1,matrix_offset+i,1);
            A.add_ij(node2,matrix_offset+i,-1);
        }
    }
    //inductor stamps
    matrix_offset = total_numofNode-1+allVoltage_source.size()+allCapacitor.size();
    for(int i=0;i<allInductor.size();i++){
        int node1 = allInductor[i]->getNodeindex1()-1;
        int node2 = allInductor[i]->getNodeindex2()-1;
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            A.add_ij(matrix_offset+i,node2,1);
            A.add_ij(node2,matrix_offset+i,1);
        }else if(node2<0){
            A.add_ij(matrix_offset+i,node1,-1);
            A.add_ij(node1,matrix_offset+i,-1);
        }else{
            A.add_ij(matrix_offset+i,node1,-1);
            A.add_ij(matrix_offset+i,node2,1);
            A.add_ij(node1,matrix_offset+i,-1);
            A.add_ij(node2,matrix_offset+i,1);
        }
    }
    //VCCS stamps

    for(int i=0;i<allVCCS.size();i++){
        int node1 = allVCCS[i]->getNodeindex1()-1;//1 --> 2
        int node2 = allVCCS[i]->getNodeindex2()-1;
        int s_node1 = getDependantNode(allVCCS[i]->getDependantNode1())-1;
        int s_node2 = getDependantNode(allVCCS[i]->getDependantNode2())-1;

        double G = allVCCS[i]->getCoefficient();

        if(node1<0&&node2<0){
            continue;
        }else if(s_node1<0&&s_node2<0){
            continue;
        }else{
            if(node1>=0&&s_node1>=0)
                A.add_ij(node1,s_node1,G);
            if(node1>=0&&s_node2>=0)
                A.add_ij(node1,s_node2,-G);
            if(node2>=0&&s_node1>=0)
                A.add_ij(node2,s_node1,-G);
            if(node2>=0&&s_node2>=0)
                A.add_ij(node2,s_node2,G);
        }
    }

    //VCVS stamps
    matrix_offset += allInductor.size();
    for(int i=0;i<allVCVS.size();i++){
        int node1 = allVCVS[i]->getNodeindex1()-1;//-
        int node2 = allVCVS[i]->getNodeindex2()-1;//+
        int s_node1 = getDependantNode(allVCVS[i]->getDependantNode1())-1;
        int s_node2 = getDependantNode(allVCVS[i]->getDependantNode2())-1;
        double G = allVCVS[i]->getCoefficient();
        if(node1<0&&node2<0){
            continue;
        }else if(s_node1<0&&s_node2<0){
            continue;
        }else if(node1<0){
            if(s_node1<0){
                A.add_ij(matrix_offset+i,node2,1);
                A.add_ij(matrix_offset+i,s_node2,G);
                A.add_ij(node2,matrix_offset+i,1);
            }else if(s_node2<0){
                A.add_ij(matrix_offset+i,node2,1);
                A.add_ij(matrix_offset+i,s_node1,-G);
                A.add_ij(node2,matrix_offset+i,1);
            }else{
                A.add_ij(matrix_offset+i,node2,1);
                A.add_ij(matrix_offset+i,s_node2,G);
                A.add_ij(matrix_offset+i,s_node1,-G);
                A.add_ij(node2,matrix_offset+i,1);
            }
        }else if(node2<0){
            if(s_node1<0){
                A.add_ij(matrix_offset+i,node1,-1);
                A.add_ij(matrix_offset+i,s_node2,G);
                A.add_ij(node1,matrix_offset+i,-1);
            }else if(s_node2<0){
                A.add_ij(matrix_offset+i,node1,-1);
                A.add_ij(matrix_offset+i,s_node1,-G);
                A.add_ij(node1,matrix_offset+i,-1);
            }else{
                A.add_ij(matrix_offset+i,node1,-1);
                A.add_ij(matrix_offset+i,s_node2,G);
                A.add_ij(matrix_offset+i,s_node1,-G);
                A.add_ij(node1,matrix_offset+i,-1);
            }
        }else{
            if(s_node1<0){
                A.add_ij(node2,matrix_offset+i,1);
                A.add_ij(matrix_offset+i,node2,1);
                A.add_ij(matrix_offset+i,node1,-1);
                A.add_ij(node1,matrix_offset+i,-1);
                A.add_ij(matrix_offset+i,s_node2,G);
            }else if(s_node2<0){
                A.add_ij(node2,matrix_offset+i,1);
                A.add_ij(matrix_offset+i,node2,1);
                A.add_ij(matrix_offset+i,node1,-1);
                A.add_ij(node1,matrix_offset+i,-1);
                A.add_ij(matrix_offset+i,s_node1,-G);
            }else{
                A.add_ij(node2,matrix_offset+i,1);
                A.add_ij(matrix_offset+i,node2,1);
                A.add_ij(matrix_offset+i,node1,-1);
                A.add_ij(node1,matrix_offset+i,-1);
                A.add_ij(matrix_offset+i,s_node2,G);
                A.add_ij(matrix_offset+i,s_node1,-G);
            }
        }
    }
    //CCCS stamps
    int matrix_offsetCCCS = total_numofNode-1;
    for(int i=0;i<allCCCS.size();i++){
        int node1 = allCCCS[i]->getNodeindex1()-1;//1 ---> 2
        int node2 = allCCCS[i]->getNodeindex2()-1;
        int vs_num=0;
        double G = allCCCS[i]->getCoefficient();
        Component* s_node = getDependantBranch(allCCCS[i]->getDependantBranchName());
        voltage_source* vs = dynamic_cast<voltage_source*>(s_node);
        if(!vs){
            qDebug()<<"Wrong usage";
        }else{
            vs_num = vs->get_num();
        }
        if(node1>=0)
            A.add_ij(node1,matrix_offsetCCCS+vs_num,G);
        if(node2>=0)
            A.add_ij(node2,matrix_offsetCCCS+vs_num,-G);
    }
    matrix_offset += allVCVS.size();
    int matrix_offsetCCVS = total_numofNode-1;
    for(int i=0;i<allCCVS.size();i++){
        int node1 = allCCVS[i]->getNodeindex1()-1;//-
        int node2 = allCCVS[i]->getNodeindex2()-1;//+
        int vs_num=0;
        double G = allCCVS[i]->getCoefficient();
        Component* s_node = getDependantBranch(allCCVS[i]->getDependantBranchName());
        voltage_source* vs = dynamic_cast<voltage_source*>(s_node);
        if(!vs){
            qDebug()<<"Wrong usage";
        }else{
            vs_num = vs->get_num();
        }
        if(node1>=0){
            A.add_ij(matrix_offset+i,node1,-1);
            A.add_ij(node1,matrix_offset+i,-1);
        }
        if(node2>=0){
            A.add_ij(matrix_offset+i,node2,1);
            A.add_ij(node2,matrix_offset+i,1);
        }
        A.add_ij(matrix_offset+i,matrix_offsetCCVS+vs_num,-G);
    }
    for(int i=0;i<allDiode.size();i++){
        int node1 = allDiode[i]->getNodeindex1()-1; // 1 --|>-- 2
        int node2 = allDiode[i]->getNodeindex2()-1;
        double Isat = allDiode[i]->get_Isat();
        double Vd = last_state(node1,0)-last_state(node2,0);
        double v_on = 0.025*log(0.025/(sqrt(2)*allDiode[i]->get_Isat()));
        if(Vd<v_on)
            continue;
        double G = 40*Isat*exp(40*Vd);
        //double Io = (exp(40*Vd)-1) - G*Vd;
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            A.add_ij(node2,node2,G);
            //b.add_ij(node2,0,Io);

        }else if(node2<0){
            A.add_ij(node1,node1,G);
            //b.add_ij(node1,0,-Io);
        }else{
            A.add_ij(node1,node1,G);
            A.add_ij(node1,node2,-G);
            A.add_ij(node2,node1,-G);
            A.add_ij(node2,node2,G);
           // b.add_ij(node1,0,-Io);
           // b.add_ij(node2,0,Io);
        }
    }



    A.debug();
    b.debug();
    Matrix test = A.solve_gauss_elimination(b);
    A.debug();
    b.debug();
    //Matrix ans = A.solve(b);
    //Matrix test = A.solve_gauss_elimination(b);

    //qDebug()<<"ans";
    //ans.debug();
    //qDebug()<<"test";
    //test.debug();

    return test;
}
void Circuit::update_A_b(Matrix &A,Matrix &b,Matrix last_state,double timestep,double current_time)
{
    int matrix_offset=0;
    A = sys.ini_A;
    b.setall(0);
    //current_source stamps
    for(int i=0;i<allCurrent_source.size();i++){
        int node1 = allCurrent_source[i]->getNodeindex1()-1; // 1->2
        int node2 = allCurrent_source[i]->getNodeindex2()-1;
        double current = allCurrent_source[i]->get_current(current_time);
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            b.add_ij(node2,0,current);
        }else if(node2<0){
            b.add_ij(node1,0,current);
        }else{
            b.add_ij(node1,0,current);
            b.add_ij(node2,0,-current);
        }
    }
    //voltage_source stamps
    matrix_offset = total_numofNode-1;
    for(int i=0;i<allVoltage_source.size();i++){
        int node1 = allVoltage_source[i]->getNodeindex1()-1; //-
        int node2 = allVoltage_source[i]->getNodeindex2()-1; //+
        double voltage = allVoltage_source[i]->get_voltage(current_time);

        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            b.add_ij(matrix_offset+i,0,voltage);
        }else if(node2<0){
            b.add_ij(matrix_offset+i,0,-voltage);
        }else{
            b.add_ij(matrix_offset+i,0,voltage);
        }
    }
    //capacitor stamps
    matrix_offset = total_numofNode-1+allVoltage_source.size();
    for(int i=0;i<allCapacitor.size();i++){
        int node1 = allCapacitor[i]->getNodeindex1()-1;
        int node2 = allCapacitor[i]->getNodeindex2()-1;
        double capacitance = allCapacitor[i]->get_capacitance();
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            A.add_ij(matrix_offset+i,node2,-capacitance/timestep);
            b.add_ij(matrix_offset+i,0, capacitance * (-last_state(node2,0)) /timestep);
        }else if(node2<0){
            A.add_ij(matrix_offset+i,node1,capacitance/timestep);
            b.add_ij(matrix_offset+i,0,capacitance * (last_state(node1,0)) /timestep);
        }else{
            A.add_ij(matrix_offset+i,node1,capacitance/timestep);
            A.add_ij(matrix_offset+i,node2,-capacitance/timestep);
            b.add_ij(matrix_offset+i,0,capacitance*(last_state(node1,0)-last_state(node2,0))/timestep);
        }


    }

    //inductor stamps
    matrix_offset = total_numofNode-1+allVoltage_source.size()+allCapacitor.size();
    for(int i=0;i<allInductor.size();i++){
        int node1 = allInductor[i]->getNodeindex1()-1;
        int node2 = allInductor[i]->getNodeindex2()-1;
        double inductance = allInductor[i]->getInductance();
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            A.add_ij(matrix_offset+i,matrix_offset+i,-inductance/timestep);
            b.add_ij(matrix_offset+i,0,-inductance*last_state(matrix_offset+i,0)/timestep);

        }else if(node2<0){
            A.add_ij(matrix_offset+i,matrix_offset+i,-inductance/timestep);
            b.add_ij(matrix_offset+i,0,-inductance*last_state(matrix_offset+i,0)/timestep);

        }else{
            A.add_ij(matrix_offset+i,matrix_offset+i,-inductance/timestep);
            b.add_ij(matrix_offset+i,0,-inductance*last_state(matrix_offset+i,0)/timestep);
        }
    }
    /*
    for(int i=0;i<allDiode.size();i++){
        int node1 = allDiode[i]->getNodeindex1()-1; // 1 --|>-- 2
        int node2 = allDiode[i]->getNodeindex2()-1;
        double Isat = allDiode[i]->get_Isat();
        double Vd = last_state(node1,0)-last_state(node2,0);
        double G = 40*Isat*exp(40*Vd);
        //double Io = (exp(40*Vd)-1) - G*Vd;
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            A.add_ij(node2,node2,G);
            //b.add_ij(node2,0,Io);

        }else if(node2<0){
            A.add_ij(node1,node1,G);
            //b.add_ij(node1,0,-Io);
        }else{
            A.add_ij(node1,node1,G);
            A.add_ij(node1,node2,-G);
            A.add_ij(node2,node1,-G);
            A.add_ij(node2,node2,G);
           // b.add_ij(node1,0,-Io);
           // b.add_ij(node2,0,Io);
        }
    }*/
}

void Circuit::sort_the_allcomponent()
{
    allResistor.clear();
    allInductor.clear();
    allCapacitor.clear();
    allVoltage_source.clear();
    allCurrent_source.clear();
    allDiode.clear();
    allCCCS.clear();
    allCCVS.clear();
    allVCCS.clear();
    allVCVS.clear();
    for(int i=0;i<allComponent.size();i++)
    {
        Resistor* re = dynamic_cast<Resistor*>(allComponent[i]);
        Inductor* in = dynamic_cast<Inductor*>(allComponent[i]);
        Capacitor* ca = dynamic_cast<Capacitor*>(allComponent[i]);
        voltage_source* vs = dynamic_cast<voltage_source*>(allComponent[i]);
        current_source* cs = dynamic_cast<current_source*>(allComponent[i]);
        Diode* dio = dynamic_cast<Diode*>(allComponent[i]);
        Current_control_current_source* CCCS = dynamic_cast<Current_control_current_source*>(allComponent[i]);
        Current_control_voltage_source* CCVS = dynamic_cast<Current_control_voltage_source*>(allComponent[i]);
        Voltage_control_current_source* VCCS = dynamic_cast<Voltage_control_current_source*>(allComponent[i]);
        Voltage_control_voltage_source* VCVS = dynamic_cast<Voltage_control_voltage_source*>(allComponent[i]);
        if(re){
            allResistor.push_back(re);
        }else if(in){
            allInductor.push_back(in);
        }else if(ca){
            allCapacitor.push_back(ca);
        }else if(vs){
            allVoltage_source.push_back(vs);
        }else if(cs){
            allCurrent_source.push_back(cs);
        }else if(dio){
            allDiode.push_back(dio);
        }else if(CCCS){
            allCCCS.push_back(CCCS);
        }else if(CCVS){
            allCCVS.push_back(CCVS);
        }else if(VCCS){
            allVCCS.push_back(VCCS);
        }else if(VCVS){
            allVCVS.push_back(VCVS);
        }
    }
    qDebug()<<"resistor: "<<allResistor.size();
    qDebug()<<"inductor: "<<allInductor.size();
    qDebug()<<"capacitor: "<<allCapacitor.size();
    qDebug()<<"voltage_source: "<<allVoltage_source.size();
    qDebug()<<"current_source: "<<allCurrent_source.size();
    qDebug()<<"diode: "<<allDiode.size();
    qDebug()<<"CCCS: "<<allCCCS.size();
    qDebug()<<"CCVS: "<<allCCVS.size();
    qDebug()<<"VCCS: "<<allVCCS.size();
    qDebug()<<"VCVS: "<<allVCVS.size();

    find_initial_condition();
}
Matrix Circuit::get_jacobian(Matrix last_state,double timestep)
{

    int num_of_unknown = total_numofNode-1;//without ground
    num_of_unknown += allVoltage_source.size();
    num_of_unknown += allCapacitor.size();
    num_of_unknown += allInductor.size();
    num_of_unknown += allVCVS.size();
    num_of_unknown += allCCVS.size();
    Matrix J(num_of_unknown,num_of_unknown,0);

    //resistor stamps

    int matrix_offset=0;
    for(int i=0;i<allResistor.size();i++){
        int node1 = allResistor[i]->getNodeindex1()-1;
        int node2 = allResistor[i]->getNodeindex2()-1;
        double conductance = 1/allResistor[i]->get_resistance();
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            J.add_ij(node2,node2,conductance);
        }else if(node2<0){
            J.add_ij(node1,node1,conductance);
        }else{
            J.add_ij(node1,node1,conductance);
            J.add_ij(node2,node2,conductance);
            J.add_ij(node1,node2,-conductance);
            J.add_ij(node2,node1,-conductance);
        }
    }
    /*
    //current_source stamps
    for(int i=0;i<allCurrent_source.size();i++){
        int node1 = allCurrent_source[i]->getNodeindex1()-1; // 1->2
        int node2 = allCurrent_source[i]->getNodeindex2()-1;
        double current = allCurrent_source[i]->get_current(0);
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            sys.b->add_ij(node2,0,current);
        }else if(node2<0){
            sys.b->add_ij(node1,0,current);
        }else{
            sys.b->add_ij(node1,0,current);
            sys.b->add_ij(node2,0,-current);
        }
    }
    */
    //voltage_source stamps
    matrix_offset = total_numofNode-1;
    for(int i=0;i<allVoltage_source.size();i++){
        int node1 = allVoltage_source[i]->getNodeindex1()-1; //-
        int node2 = allVoltage_source[i]->getNodeindex2()-1; //+
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            J.add_ij(matrix_offset+i,node2,1);
            J.add_ij(node2,matrix_offset+i,1);
        }else if(node2<0){
            J.add_ij(matrix_offset+i,node2,1);
            J.add_ij(node2,matrix_offset+i,1);
        }else{
            J.add_ij(matrix_offset+i,node2,1);
            J.add_ij(node2,matrix_offset+i,1);
            J.add_ij(matrix_offset+i,node1,-1);
            J.add_ij(node1,matrix_offset+i,-1);
        }
    }
    //capacitor stamps
    matrix_offset = total_numofNode-1+allVoltage_source.size();
    for(int i=0;i<allCapacitor.size();i++){
        int node1 = allCapacitor[i]->getNodeindex1()-1;
        int node2 = allCapacitor[i]->getNodeindex2()-1;
        double capacitance = allCapacitor[i]->get_capacitance();
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){

            J.add_ij(node2,matrix_offset+i,-1);
            J.add_ij(matrix_offset+i,node2,-capacitance/timestep);
        }else if(node2<0){

            J.add_ij(node1,matrix_offset+i,1);
            J.add_ij(matrix_offset+i,node1,capacitance/timestep);

        }else{
            J.add_ij(node1,matrix_offset+i,1);
            J.add_ij(node2,matrix_offset+i,-1);
            J.add_ij(matrix_offset+i,node1,capacitance/timestep);
            J.add_ij(matrix_offset+i,node2,-capacitance/timestep);
        }
    }
    //inductor stamps
    matrix_offset = total_numofNode-1+allVoltage_source.size()+allCapacitor.size();
    for(int i=0;i<allInductor.size();i++){
        int node1 = allInductor[i]->getNodeindex1()-1;
        int node2 = allInductor[i]->getNodeindex2()-1;
        double inductance = allInductor[i]->getInductance();
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){

            J.add_ij(node2,matrix_offset+i,1);
            J.add_ij(matrix_offset+i,node2,timestep/inductance);

        }else if(node2<0){

            J.add_ij(node1,matrix_offset+i,-1);
            J.add_ij(matrix_offset+i,node1,-timestep/inductance);

        }else{
            J.add_ij(node1,matrix_offset+i,-1);
            J.add_ij(node2,matrix_offset+i,1);
            J.add_ij(matrix_offset+i,node1,-timestep/inductance);
            J.add_ij(matrix_offset+i,node2,timestep/inductance);
        }
    }

    for(int i=0;i<allDiode.size();i++){
        int node1 = allDiode[i]->getNodeindex1()-1; // 1 --|>-- 2
        int node2 = allDiode[i]->getNodeindex2()-1;
        double Isat = allDiode[i]->get_Isat();
        double Vd = last_state(node1,0)-last_state(node2,0);
        if(Vd<=0)
            continue;
        double G = 40*Isat*exp(40*Vd);
        if(isinf(G))
            continue;
        //double Io = (exp(40*Vd)-1) - G*Vd;
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            J.add_ij(node2,node2,G);
            //b.add_ij(node2,0,Io);

        }else if(node2<0){
            J.add_ij(node1,node1,G);
            //b.add_ij(node1,0,-Io);
        }else{
            J.add_ij(node1,node1,G);
            J.add_ij(node1,node2,-G);
            J.add_ij(node2,node1,-G);
            J.add_ij(node2,node2,G);
           // b.add_ij(node1,0,-Io);
           // b.add_ij(node2,0,Io);
        }
    }




    //VCCS stamps not done
    for(int i=0;i<allVCCS.size();i++){
        int node1 = allVCCS[i]->getNodeindex1()-1;//1 --> 2
        int node2 = allVCCS[i]->getNodeindex2()-1;
        int s_node1 = getDependantNode(allVCCS[i]->getDependantNode1())-1;
        int s_node2 = getDependantNode(allVCCS[i]->getDependantNode2())-1;
        double G = allVCCS[i]->getCoefficient();
        if(node1<0&&node2<0){
            continue;
        }else if(s_node1<0&&s_node2<0){
            continue;
        }else if(node1<0){
            if(s_node1<0){
                J.add_ij(node2,s_node2,G);
            }else if(s_node2<0){
                J.add_ij(node2,s_node1,-G);
            }else{
                J.add_ij(node2,s_node2,G);
                J.add_ij(node2,s_node1,-G);
            }
        }else if(node2<0){
            if(s_node1<0){
                J.add_ij(node1,s_node2,-G);
            }else if(s_node2<0){
                J.add_ij(node1,s_node1,G);
            }else{
                J.add_ij(node1,s_node2,-G);
                J.add_ij(node1,s_node1,G);
            }
        }else{
            if(s_node1<0){
                J.add_ij(node1,s_node2,-G);
                J.add_ij(node2,s_node2,G);
            }else if(s_node2<0){
                J.add_ij(node1,s_node1,G);
                J.add_ij(node2,s_node1,-G);
            }else{
                J.add_ij(node1,s_node1,-G);
                J.add_ij(node1,s_node2,G);
                J.add_ij(node2,s_node1,-G);
                J.add_ij(node2,s_node2,G);
            }
        }
    }
    //VCVS stamps
    matrix_offset += allInductor.size();
    for(int i=0;i<allVCVS.size();i++){
        int node1 = allVCVS[i]->getNodeindex1()-1;//-
        int node2 = allVCVS[i]->getNodeindex2()-1;//+
        int s_node1 = getDependantNode(allVCVS[i]->getDependantNode1())-1;
        int s_node2 = getDependantNode(allVCVS[i]->getDependantNode2())-1;
        double A = allVCVS[i]->getCoefficient();
        if(node1<0&&node2<0){
            continue;
        }else if(s_node1<0&&s_node2<0){
            continue;
        }else if(node1<0){
            if(s_node1<0){
                J.add_ij(matrix_offset+i,node2,1);
                J.add_ij(matrix_offset+i,s_node2,A);
                J.add_ij(node2,matrix_offset+i,1);
            }else if(s_node2<0){
                J.add_ij(matrix_offset+i,node2,1);
                J.add_ij(matrix_offset+i,s_node1,-A);
                J.add_ij(node2,matrix_offset+i,1);
            }else{
                J.add_ij(matrix_offset+i,node2,1);
                J.add_ij(matrix_offset+i,s_node2,A);
                J.add_ij(matrix_offset+i,s_node1,-A);
                J.add_ij(node2,matrix_offset+i,1);
            }
        }else if(node2<0){
            if(s_node1<0){
                J.add_ij(matrix_offset+i,node1,-1);
                J.add_ij(matrix_offset+i,s_node2,A);
                J.add_ij(node1,matrix_offset+i,-1);
            }else if(s_node2<0){
                J.add_ij(matrix_offset+i,node1,-1);
                J.add_ij(matrix_offset+i,s_node1,-A);
                J.add_ij(node1,matrix_offset+i,-1);
            }else{
                J.add_ij(matrix_offset+i,node1,-1);
                J.add_ij(matrix_offset+i,s_node2,A);
                J.add_ij(matrix_offset+i,s_node1,-A);
                J.add_ij(node1,matrix_offset+i,-1);
            }
        }else{
            if(s_node1<0){
                J.add_ij(node2,matrix_offset+i,1);
                J.add_ij(matrix_offset+i,node2,1);
                J.add_ij(matrix_offset+i,node1,-1);
                J.add_ij(node1,matrix_offset+i,-1);
                J.add_ij(matrix_offset+i,s_node2,A);
            }else if(s_node2<0){
                J.add_ij(node2,matrix_offset+i,1);
                J.add_ij(matrix_offset+i,node2,1);
                J.add_ij(matrix_offset+i,node1,-1);
                J.add_ij(node1,matrix_offset+i,-1);
                J.add_ij(matrix_offset+i,s_node1,-A);
            }else{
                J.add_ij(node2,matrix_offset+i,1);
                J.add_ij(matrix_offset+i,node2,1);
                J.add_ij(matrix_offset+i,node1,-1);
                J.add_ij(node1,matrix_offset+i,-1);
                J.add_ij(matrix_offset+i,s_node2,A);
                J.add_ij(matrix_offset+i,s_node1,-A);
            }
        }
    }
    //CCCS stamps
    int matrix_offsetCCCS = total_numofNode-1;
    for(int i=0;i<allCCCS.size();i++){
        int node1 = allCCCS[i]->getNodeindex1()-1;//1 ---> 2
        int node2 = allCCCS[i]->getNodeindex2()-1;
        int vs_num=0;
        double A = allCCCS[i]->getCoefficient();
        Component* s_node = getDependantBranch(allCCCS[i]->getDependantBranchName());
        voltage_source* vs = dynamic_cast<voltage_source*>(s_node);
        if(!vs){
            qDebug()<<"Wrong usage";
        }else{
            vs_num = vs->get_num();
        }
        if(node1>=0)
            J.add_ij(node1,matrix_offsetCCCS+vs_num,A);
        if(node2>=0)
            J.add_ij(node2,matrix_offsetCCCS+vs_num,-A);
    }
    matrix_offset += allVCVS.size();
    int matrix_offsetCCVS = total_numofNode-1;
    for(int i=0;i<allCCVS.size();i++){
        int node1 = allCCVS[i]->getNodeindex1()-1;//-
        int node2 = allCCVS[i]->getNodeindex2()-1;//+
        int vs_num=0;
        double A = allCCVS[i]->getCoefficient();
        Component* s_node = getDependantBranch(allCCVS[i]->getDependantBranchName());
        voltage_source* vs = dynamic_cast<voltage_source*>(s_node);
        if(!vs){
            qDebug()<<"Wrong usage";
        }else{
            vs_num = vs->get_num();
        }
        if(node1>=0){
            J.add_ij(matrix_offset+i,node1,-1);
            J.add_ij(node1,matrix_offset+i,-1);
        }
        if(node2>=0){
            J.add_ij(matrix_offset+i,node2,1);
            J.add_ij(node2,matrix_offset+i,1);
        }
        J.add_ij(matrix_offset+i,matrix_offsetCCVS+vs_num,-A);
    }


    return J;
}
void Circuit::resetAllNodeIndex()
{
    for(auto c:allComponent){
        c->resetNodeIndex();
    }
    for(auto g:allGround){
        g->resetNodeIndex();
    }
    for(auto l:allLine){
        l->resetNodeIndex();
    }
}
void Circuit::push_backComponent(Component *c)
{
    allComponent.push_back(c);
}
void Circuit::push_backLine(LineNodeitem *l)
{
    allLine.push_back(l);
}
void Circuit::push_backGround(Ground *g)
{
    allGround.push_back(g);
}
void Circuit::deleteComponent(int index)
{
    allComponent.erase(allComponent.begin() + index);
}

void Circuit::deleteAllComponent()
{
    for(int i=0;i<allComponent.size();i++)
        delete allComponent[i];
    allComponent.clear();
}
int Circuit::get_circuit_state()
{
    return state;
}
const QVector< QPair<Matrix,double> >& Circuit::get_solutions()
{
    return solutions;
}
int Circuit::getDependantNode(QString a)
{
    qDebug() << a;
    QChar last = a[a.size()-1];
    a.erase(a.end()-1,a.end());
    qDebug() << a;
    for(int i=0;i<allComponent.size();i++)
        if(a == allComponent[i]->getname())
        {
            if(last == 'L')
                return allComponent[i]->getNodes()[0]->getNodeIndex();
            else if(last == 'R')
                return allComponent[i]->getNodes()[1]->getNodeIndex();
        }
}
Component* Circuit::getDependantBranch(QString a)
{
    qDebug() << a;
    for(int i=0;i<allComponent.size();i++)
        if(a == allComponent[i]->getname())
        {
            return allComponent[i];
        }
}
Circuit::~Circuit()
{
    allResistor.clear();
    allInductor.clear();
    allCapacitor.clear();
    allVoltage_source.clear();
    allCurrent_source.clear();
    allDiode.clear();
    allCCCS.clear();
    allCCVS.clear();
    allVCCS.clear();
    allVCVS.clear();
    sys.clear();
    deleteAllComponent();
    for(int i=0;i<allLine.size();i++)
        delete allLine[i];
    allLine.clear();
}
/*

Matrix Circuit::analysis_circuit(double t,double timestep)
{
    //only resistor and current_source
    if(state!=ok){
        qDebug()<<"There is something wrong @@";
        return Matrix(1,1,0);
    }

    int num_of_unknown = total_numofNode-1;//without ground
    num_of_unknown += allVoltage_source.size();
    num_of_unknown += allCapacitor.size();
    num_of_unknown += allInductor.size();

    Matrix A(num_of_unknown,num_of_unknown,0);
    Matrix b(num_of_unknown,1,0);
    Matrix last_state(num_of_unknown,1,0);
    //qDebug()<<"hello";
    if(!solutions.empty()){
        last_state = solutions.back();
    }else{
        for(int i=0;i<initial_condition.size();i++){
            if(initial_condition[i].first != 0)
                last_state.set_ij(initial_condition[i].first-1,0,initial_condition[i].second);
        }
    }
    //Debug()<<"hello";
    //resistor stamps

    int matrix_offset=0;
    for(int i=0;i<allResistor.size();i++){
        int node1 = allResistor[i]->getNodeindex1()-1;
        int node2 = allResistor[i]->getNodeindex2()-1;
        double conductance = 1/allResistor[i]->get_resistance();
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            A.add_ij(node2,node2,conductance);
        }else if(node2<0){
            A.add_ij(node1,node1,conductance);
        }else{
            //qDebug()<<node1<<" "<<node2;
            A.add_ij(node1,node1,conductance);
            A.add_ij(node2,node2,conductance);
            A.add_ij(node1,node2,-conductance);
            A.add_ij(node2,node1,-conductance);
        }

    }
    //current_source stamps
    for(int i=0;i<allCurrent_source.size();i++){
        int node1 = allCurrent_source[i]->getNodeindex1()-1; // 1->2
        int node2 = allCurrent_source[i]->getNodeindex2()-1;
        double current = allCurrent_source[i]->get_current(t);
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            b.add_ij(node2,0,current);
        }else if(node2<0){
            b.add_ij(node1,0,current);
        }else{
            b.add_ij(node1,0,current);
            b.add_ij(node2,0,-current);
        }
    }
    //voltage_source stamps
    matrix_offset = total_numofNode-1;
    for(int i=0;i<allVoltage_source.size();i++){
        int node1 = allVoltage_source[i]->getNodeindex1()-1; //-
        int node2 = allVoltage_source[i]->getNodeindex2()-1; //+
        double voltage = allVoltage_source[i]->get_voltage(t);
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            A.add_ij(matrix_offset+i,node2,1);
            A.add_ij(node2,matrix_offset+i,1);
            b.add_ij(matrix_offset+i,0,voltage);
        }else if(node2<0){
            A.add_ij(matrix_offset+i,node2,1);
            A.add_ij(node2,matrix_offset+i,1);
            b.add_ij(matrix_offset+i,0,-voltage);
        }else{
            A.add_ij(matrix_offset+i,node2,1);
            A.add_ij(node2,matrix_offset+i,1);
            A.add_ij(matrix_offset+i,node1,-1);
            A.add_ij(node1,matrix_offset+i,-1);
            b.add_ij(matrix_offset+i,0,voltage);
        }
    }
    //capacitor stamps
    matrix_offset = total_numofNode-1+allVoltage_source.size();
    for(int i=0;i<allCapacitor.size();i++){
        int node1 = allCapacitor[i]->getNodeindex1()-1;
        int node2 = allCapacitor[i]->getNodeindex2()-1;
        double capacitance = allCapacitor[i]->get_capacitance();
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            A.add_ij(matrix_offset+i,node2,capacitance/timestep);
            A.set_ij(matrix_offset+i,matrix_offset+i,-1);
            A.add_ij(node2,matrix_offset+i,1);
            b.add_ij(matrix_offset+i,0, capacitance * (last_state(node2,0)) /timestep);
        }else if(node2<0){
            A.add_ij(matrix_offset+i,node1,-capacitance/timestep);
            A.set_ij(matrix_offset+i,matrix_offset+i,-1);
            A.add_ij(node1,matrix_offset+i,-1);
            b.add_ij(matrix_offset+i,0,capacitance * (-last_state(node1,0)) /timestep);
        }else{
            A.add_ij(matrix_offset+i,node1,-capacitance/timestep);
            A.add_ij(matrix_offset+i,node2,capacitance/timestep);
            A.set_ij(matrix_offset+i,matrix_offset+i,-1);
            A.add_ij(node1,matrix_offset+i,-1);
            A.add_ij(node2,matrix_offset+i,1);
            b.add_ij(matrix_offset+i,0,capacitance*(last_state(node2,0)-last_state(node1,0))/timestep);
        }
    }
    //inductor stamps
    matrix_offset = total_numofNode-1+allVoltage_source.size()+allCapacitor.size();
    for(int i=0;i<allInductor.size();i++){
        int node1 = allInductor[i]->getNodeindex1()-1;
        int node2 = allInductor[i]->getNodeindex2()-1;
        double inductance = allInductor[i]->getInductance();
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            A.add_ij(matrix_offset+i,node2,1);
            A.add_ij(matrix_offset+i,matrix_offset+i,-inductance/timestep);
            A.add_ij(node2,matrix_offset+i,1);
            b.add_ij(matrix_offset+i,0,-inductance*last_state(matrix_offset+i,0)/timestep);
        }else if(node2<0){
            A.add_ij(matrix_offset+i,node1,-1);
            A.add_ij(matrix_offset+i,matrix_offset+i,-inductance/timestep);
            A.add_ij(node1,matrix_offset+i,-1);
            b.add_ij(matrix_offset+i,0,-inductance*last_state(matrix_offset+i,0)/timestep);
        }else{
            A.add_ij(matrix_offset+i,node1,-1);
            A.add_ij(matrix_offset+i,node2,1);
            A.add_ij(matrix_offset+i,matrix_offset+i,-inductance/timestep);
            A.add_ij(node1,matrix_offset+i,-1);
            A.add_ij(node2,matrix_offset+i,1);
            b.add_ij(matrix_offset+i,0,-inductance*last_state(matrix_offset+i,0)/timestep);
        }
    }
    Matrix test = A.solve_gauss_elimination(b);
    //A.debug();
    //b.debug();
    //Matrix ans = A.solve(b);
    //Matrix test = A.solve_gauss_elimination(b);

    //qDebug()<<"ans";
    //ans.debug();
    //qDebug()<<"test";
    //test.debug();

    return test;
}

QVector<Matrix> Circuit::analysis_circuit_timeinterval(double t)
{
    solutions.clear();
    double time_step = t/10000;
    double max_timestep = t/1000;
    double min_timestep = t/100000;
    double current_time = 0;

    while(current_time<=t){
        solutions.push_back(analysis_circuit(current_time,time_step));
        current_time+=time_step;
    }
    return solutions;
}



    int num_of_unknown = total_numofNode-1;//without ground
    num_of_unknown += allVoltage_source.size();
    num_of_unknown += allCapacitor.size();
    num_of_unknown += allInductor.size();
    sys.A = new Matrix(num_of_unknown,num_of_unknown,0);
    sys.b = new Matrix(num_of_unknown,1,0);
    sys.ini = true;
    //resistor stamps

    int matrix_offset=0;
    for(int i=0;i<allResistor.size();i++){
        int node1 = allResistor[i]->getNodeindex1()-1;
        int node2 = allResistor[i]->getNodeindex2()-1;
        double conductance = 1/allResistor[i]->get_resistance();
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            sys.A->add_ij(node2,node2,conductance);
        }else if(node2<0){
            sys.A->add_ij(node1,node1,conductance);
        }else{
            //qDebug()<<node1<<" "<<node2;
            sys.A->add_ij(node1,node1,conductance);
            sys.A->add_ij(node2,node2,conductance);
            sys.A->add_ij(node1,node2,-conductance);
            sys.A->add_ij(node2,node1,-conductance);
        }

    }

    //current_source stamps
    for(int i=0;i<allCurrent_source.size();i++){
        int node1 = allCurrent_source[i]->getNodeindex1()-1; // 1->2
        int node2 = allCurrent_source[i]->getNodeindex2()-1;
        double current = allCurrent_source[i]->get_current(0);
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            sys.b->add_ij(node2,0,current);
        }else if(node2<0){
            sys.b->add_ij(node1,0,current);
        }else{
            sys.b->add_ij(node1,0,current);
            sys.b->add_ij(node2,0,-current);
        }
    }
    //voltage_source stamps
    matrix_offset = total_numofNode-1;
    for(int i=0;i<allVoltage_source.size();i++){
        int node1 = allVoltage_source[i]->getNodeindex1()-1; //-
        int node2 = allVoltage_source[i]->getNodeindex2()-1; //+
        double voltage = allVoltage_source[i]->get_voltage(0);
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            sys.A->add_ij(matrix_offset+i,node2,1);
            sys.A->add_ij(node2,matrix_offset+i,1);
            sys.b->add_ij(matrix_offset+i,0,voltage);
        }else if(node2<0){
            sys.A->add_ij(matrix_offset+i,node2,1);
            sys.A->add_ij(node2,matrix_offset+i,1);
            sys.b->add_ij(matrix_offset+i,0,-voltage);
        }else{
            sys.A->add_ij(matrix_offset+i,node2,1);
            sys.A->add_ij(node2,matrix_offset+i,1);
            sys.A->add_ij(matrix_offset+i,node1,-1);
            sys.A->add_ij(node1,matrix_offset+i,-1);
            sys.b->add_ij(matrix_offset+i,0,voltage);
        }
    }
     sys.ini_A = *sys.A;
    //capacitor stamps
    matrix_offset = total_numofNode-1+allVoltage_source.size();
    for(int i=0;i<allCapacitor.size();i++){
        int node1 = allCapacitor[i]->getNodeindex1()-1;
        int node2 = allCapacitor[i]->getNodeindex2()-1;
        double capacitance = allCapacitor[i]->get_capacitance();
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            sys.A->add_ij(matrix_offset+i,node2,capacitance/timestep);
            sys.A->set_ij(matrix_offset+i,matrix_offset+i,-1);
            sys.A->add_ij(node2,matrix_offset+i,1);
            sys.b->add_ij(matrix_offset+i,0, capacitance * (ini_state(node2,0)) /timestep);

            sys.ini_A.set_ij(matrix_offset+i,matrix_offset+i,-1);
            sys.ini_A.add_ij(node2,matrix_offset+i,1);

        }else if(node2<0){
            sys.A->add_ij(matrix_offset+i,node1,-capacitance/timestep);
            sys.A->set_ij(matrix_offset+i,matrix_offset+i,-1);
            sys.A->add_ij(node1,matrix_offset+i,-1);
            sys.b->add_ij(matrix_offset+i,0,capacitance * (-ini_state(node1,0)) /timestep);

            sys.ini_A.set_ij(matrix_offset+i,matrix_offset+i,-1);
            sys.ini_A.add_ij(node1,matrix_offset+i,-1);

        }else{
            sys.A->add_ij(matrix_offset+i,node1,-capacitance/timestep);
            sys.A->add_ij(matrix_offset+i,node2,capacitance/timestep);
            sys.A->set_ij(matrix_offset+i,matrix_offset+i,-1);
            sys.A->add_ij(node1,matrix_offset+i,-1);
            sys.A->add_ij(node2,matrix_offset+i,1);
            sys.b->add_ij(matrix_offset+i,0,capacitance*(ini_state(node2,0)-ini_state(node1,0))/timestep);

            sys.ini_A.set_ij(matrix_offset+i,matrix_offset+i,-1);
            sys.ini_A.add_ij(node1,matrix_offset+i,-1);
            sys.ini_A.add_ij(node2,matrix_offset+i,1);

        }
    }
    //inductor stamps
    matrix_offset = total_numofNode-1+allVoltage_source.size()+allCapacitor.size();
    for(int i=0;i<allInductor.size();i++){
        int node1 = allInductor[i]->getNodeindex1()-1;
        int node2 = allInductor[i]->getNodeindex2()-1;
        double inductance = allInductor[i]->getInductance();
        if(node1<0&&node2<0){
            continue;
        }else if(node1<0){
            sys.A->add_ij(matrix_offset+i,node2,1);
            sys.A->add_ij(matrix_offset+i,matrix_offset+i,-inductance/timestep);
            sys.A->add_ij(node2,matrix_offset+i,1);
            sys.b->add_ij(matrix_offset+i,0,-inductance*ini_state(matrix_offset+i,0)/timestep);

            sys.ini_A.add_ij(matrix_offset+i,node2,1);
            sys.ini_A.add_ij(node2,matrix_offset+i,1);

        }else if(node2<0){
            sys.A->add_ij(matrix_offset+i,node1,-1);
            sys.A->add_ij(matrix_offset+i,matrix_offset+i,-inductance/timestep);
            sys.A->add_ij(node1,matrix_offset+i,-1);
            sys.b->add_ij(matrix_offset+i,0,-inductance*ini_state(matrix_offset+i,0)/timestep);

            sys.ini_A.add_ij(matrix_offset+i,node1,-1);
            sys.ini_A.add_ij(node1,matrix_offset+i,-1);

        }else{
            sys.A->add_ij(matrix_offset+i,node1,-1);
            sys.A->add_ij(matrix_offset+i,node2,1);
            sys.A->add_ij(matrix_offset+i,matrix_offset+i,-inductance/timestep);
            sys.A->add_ij(node1,matrix_offset+i,-1);
            sys.A->add_ij(node2,matrix_offset+i,1);
            sys.b->add_ij(matrix_offset+i,0,-inductance*ini_state(matrix_offset+i,0)/timestep);

            sys.ini_A.add_ij(matrix_offset+i,node1,-1);
            sys.ini_A.add_ij(matrix_offset+i,node2,1);
            sys.ini_A.add_ij(node1,matrix_offset+i,-1);
            sys.ini_A.add_ij(node2,matrix_offset+i,1);
        }
    }
 * */
