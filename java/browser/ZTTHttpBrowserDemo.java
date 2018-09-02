/********************************************************
 ZTT 浏览器
 *******************************************************/
import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Dimension ;
import java.net.URL;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.JTextPane;


public class ZTTHttpBrowserDemo extends  JFrame
{
    JTextField jtfAddress;
    JButton jbGo;
    JTextPane jtpShow;
    JLabel jlInfo;
    JLabel jlAddr;
    
    public ZTTHttpBrowserDemo()
    {
        super("ZTT"); 
    }
    
    public void run()
    {     
        setSize(400,300);
        JPanel panel=new JPanel();
        
         /* 布局部分我们这边不多做介绍
         * 这边设置布局为 null
         */
        panel.setLayout(null);
        panel.setSize(400,300);
        panel.setPreferredSize(new Dimension(getWidth(), getHeight()));//设置面版高度
        //updateUI();        
        
        System.out.println("width="+getWidth());
        System.out.println("Height="+getHeight());
        
        jlAddr= new JLabel("地址");
        jlAddr.setBounds(0,0,60,25);
        panel.add(jlAddr);
        
        jbGo=new JButton("go");
        jbGo.setBounds(320,0,60,25);
        panel.add(jbGo);
        jbGo.addActionListener(new ShowHTMLListener());
        
        jtfAddress=new JTextField(20);
        System.out.println("tmp="+panel.getWidth());
        System.out.println("tmp="+jlAddr.getWidth());
        System.out.println("tmp="+jbGo.getWidth());
        
        System.out.println("tmp="+(panel.getWidth()-jlAddr.getWidth()-jbGo.getWidth()-20));
        jtfAddress.setBounds(80,0,panel.getWidth()-jlAddr.getWidth()-jbGo.getWidth()-20,25);
        panel.add(jtfAddress);
        jtfAddress.addActionListener(new ShowHTMLListener());  
    
        
        
        
        jtpShow=new JTextPane();        
        JScrollPane jsp=new JScrollPane(jtpShow);  
        jsp.setBounds(10,30,360,250);        
        panel.add(jsp);
        
        jlInfo=new JLabel(); 
        panel.add(jlInfo,BorderLayout.SOUTH);
        
        Container container = getContentPane();
        container.add(panel,BorderLayout.NORTH);

        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);        
    }

    class ShowHTMLListener implements ActionListener
    {

        @Override
        public void actionPerformed(ActionEvent e) 
        {
           // TODO Auto-generated method stub
            try
            {
                jlInfo.setText("正在链接...");
                URL address=new URL(jtfAddress.getText());
                jtpShow.setPage(address);
                jlInfo.setText("完成");
            }
            catch(Exception ex){
                jlInfo.setText("链接出错，请输入正确的URL地址!");
                ex.printStackTrace();
            }
        }

    }

    public static void main(String[] args) 
    {
        ZTTHttpBrowserDemo test = new ZTTHttpBrowserDemo();
        test.run();
    }
}