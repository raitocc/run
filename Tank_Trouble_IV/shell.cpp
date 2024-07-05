#include "shell.h"

// �����ӵ�λ��
void shell::updatePosition(double deltaTime)
{
    //�ӵ����ڿ���״̬
    if(status==0)
    {
        return;
    }
    //�ӵ��ƶ�
    shell_x=shell_x + cos(tk.angle)*shell_speed * deltaTime;
    shell_y=shell_y - sin(tk.angle)*shell_speed * deltaTime;
    shell_rect.moveTo(shell_x,shell_y);
    //�ӵ�����ʱ������
    lifespan -= deltaTime;
    //�ӵ�λ�ó�����Ļ����Ϊ����״̬
    if(shell_x<=shell_rect.width()||shell_y<=-shell_rect.height())
    {
        status=0;
    }
}

// �����ӵ�
void shell::fire(QMouseEvent *event){
    if(event->button()==Qt::LeftButton)
    {
        //���ӵ��ӿ���״̬��Ϊʹ��״̬
        status=1;
        //�����ӵ�����
        shell_x=tk.tank_x;
        shell_y=tk.tank_Y-1/2*tank_length;
        shell_rect.moveTo(shell_x,shell_y);

        //�����ӵ�
        shell_painter.drawPixmap(shell_x,shell_y,my_bullet);

        double deltatime=0.01667;
        while(lifespan>0)
        {
            updatePosition(deltatime);
        }
    }
}

//�ӵ���ײ���
void shell::collisionDetection()
{
    //����ӵ����ο�͵з�̹�˾��ο��ǽ�ཻ����Ϊ����״̬
}

// �ӵ���ըЧ��
void shell::hit() {

}


