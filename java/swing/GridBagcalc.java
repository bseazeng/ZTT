package ZTT;
import javax.swing.*;
import java.awt.*;
import java.util.*;
import java.lang.*;
import java.awt.event.*; 
public class GridBagcalc implements MouseListener
{
    private JFrame jf;
    private JButton []jb;
    private JTextField jtf;
    public StringBuffer s1=new StringBuffer();
    public StringBuffer s2=new StringBuffer();
    public StringBuffer s3=new StringBuffer();
    private double result=0;
    private double source=0;
    private double dest = 0;
    private char temp = '?';
    int signal=0;
    
    public void go()
    {  
        String []s;
        jf=new JFrame("the demonstration of calculator");
        Container cp=jf.getContentPane();
        GridBagLayout gl=new GridBagLayout();
        cp.setLayout(gl);
        GridBagConstraints c=new GridBagConstraints();
        jb=new JButton[15];
        
        for(int i=1;i<=9;i++)
        {
            jb[i-1]=new JButton(""+(i-1));
            c.fill=GridBagConstraints.VERTICAL;
            if(i<4)
            c.gridy=0;
            else if(i<7)
            c.gridy=1;
            else
            c.gridy=2;
            if(i%3==0)
            c.gridx=2;
            else if(i%3==1)
            c.gridx=0;
            else if(i%3==2)
            c.gridx=1;
            gl.setConstraints(jb[i-1],c);
            cp.add(jb[i-1]);
        }
        
        jb[9]=new JButton("+");
        jb[10]=new JButton("-");
        jb[11]=new JButton("*");
        jb[12]=new JButton("/");
        jb[13]=new JButton("=");
        jb[14]=new JButton("AC");
        c.gridx=0;c.gridy=4;
        gl.setConstraints(jb[9], c);
        c.fill=GridBagConstraints.VERTICAL;
        cp.add(jb[9]);
        c.gridx=1;c.gridy=4;
        gl.setConstraints(jb[10], c);
        c.fill=GridBagConstraints.VERTICAL;
        cp.add(jb[10]);
        c.gridx=2;c.gridy=4;gl.setConstraints(jb[11], c); 
        c.fill=GridBagConstraints.VERTICAL;
        cp.add(jb[11]);
        c.gridx=3;c.gridy=4;gl.setConstraints(jb[12], c);
        c.fill=GridBagConstraints.VERTICAL;
        cp.add(jb[12]);
        c.gridx=5;c.gridy=4;gl.setConstraints(jb[13], c);
        cp.add(jb[13]);
        c.gridx=0;c.gridy=5;gl.setConstraints(jb[14], c);
        cp.add(jb[14]);
        jtf=new JTextField(9);
        jtf.setText("0.0");
        c.gridx=5;c.gridy=0;
        cp.add(jtf,c);
        jf.setSize(20, 30);
        jf.setVisible(true);
        jf.addMouseListener(this);
        for(int i=0;i<15;i++)
        jb[i].addMouseListener(this);
    }
    public static void main(String []args)
    {
        GridBagcalc calc=new GridBagcalc();
        calc.go();
    }

    @Override
    public void mouseClicked(MouseEvent e) {
    // TODO 自动生成的方法存根

    }
    @Override
    public void mousePressed(MouseEvent e) 
    {
        // TODO 自动生成的方法存根
        if(temp=='?')
        {
            for(int i=0;i<9;i++)
            if(e.getSource()==jb[i])
            {
            if(signal==0)
            s1.append(String.valueOf(i));
            else
            {
            s1.delete(0,s1.length());s1.append(source);signal=0;
            }
            jtf.setText(s1.toString());
            source=Double.valueOf(s1.toString());
            System.out.println("source"+source);
            }
        }
        if(e.getSource()==jb[9])
        {
            temp='+';
            jtf.setText(s3.append(source+"+").toString());
        }
        if(e.getSource()==jb[10])
        {
            jtf.setText(s3.append(source+"-").toString());temp='-';
        }
        if(e.getSource()==jb[11])
        { 
            temp='*';
            jtf.setText(s3.append(source+"*").toString());
        }
        if(e.getSource()==jb[12])
        {
            jtf.setText(s3.append(source+"/").toString());temp='/';
        }
        System.out.println("temp:"+temp);
        if(temp!='?')
        {
        for(int i=0;i<9;i++)
        if(e.getSource()==jb[i])
        {
        s2.append(i);
        jtf.setText(s3.append(String.valueOf(i)).toString());
        dest=Double.valueOf(s2.toString());
        System.out.println("dest:"+dest);}
               }
        if(e.getSource()==jb[13])
        {
        switch(temp){
        case'+':result=source+dest;break;
        case'-':result=source-dest;break;
        case'*':result=source*dest;break;
        case'/':result=source/dest;break;
        }
        System.out.println("source:"+source+"dest:"+dest+"result:"+result);
        jtf.setText(String.valueOf(result).toString());
        source=result;
        temp='?';
        dest=0;
        signal=1;
        s3.delete(0,s3.length());
        s2.delete(0,s2.length());
        }
        if(e.getSource()==jb[14])
        {source=dest=result=0;temp='?';signal=0;jtf.setText("0.0");
        s1.delete(0, s1.length());
        s2.delete(0, s1.length());
        s3.delete(0, s1.length());
        }
    }
    @Override
    public void mouseReleased(MouseEvent e) {
    // TODO 自动生成的方法存根

    }
    @Override
    public void mouseEntered(MouseEvent e) {
    // TODO 自动生成的方法存根

    }
    @Override
    public void mouseExited(MouseEvent e) {
    // TODO 自动生成的方法存根

    }
}