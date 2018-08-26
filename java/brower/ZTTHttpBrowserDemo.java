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

    public ZTTHttpBrowserDemo()
    {
     
        super("ZTT");
        setSize(350,280);
        //ZTTHttpBrowserDemo ztt=new ZTTHttpBrowserDemo();  
        // ztt.setLayout(new BorderLayout()); 
        
        jtfAddress=new JTextField(20);
        jbGo=new JButton("转到");
        jtpShow=new JTextPane();
        jlInfo=new JLabel();

        JPanel panel=new JPanel();
        panel.setPreferredSize(new Dimension(0, 40));//设置面版高度
        panel.add(new JLabel("地址"), BorderLayout.WEST);
        panel.add(jtfAddress, BorderLayout.CENTER );
        panel.add(jbGo, BorderLayout.EAST);
        JScrollPane jsp=new JScrollPane(jtpShow);
        Container container = getContentPane();
        container.add(panel,BorderLayout.NORTH);
        container.add(jsp,BorderLayout.CENTER);
        container.add(jlInfo,BorderLayout.SOUTH);

        jbGo.addActionListener(new ShowHTMLListener());
        jtfAddress.addActionListener(new ShowHTMLListener());   

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
        new ZTTHttpBrowserDemo();
    }
}