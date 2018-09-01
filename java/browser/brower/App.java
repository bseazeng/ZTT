package Demo.Test;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class App 
{    
    public static void readParse(String urlPath,String str) throws Exception 
    {
        System.out.println(str);
        
        ByteArrayOutputStream outStream = new ByteArrayOutputStream();
        byte[] data = new byte[1024];
        int len = 0;

        URL url = new URL(urlPath);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        // 设置传递方式
        conn.setRequestMethod("POST");
        //代理
        conn.addRequestProperty("User-Agent", "Mozilla/4.0 (compatible; MSIE 5.0; Windows NT; DigExt)");
        
        conn.setRequestProperty("Content-Type", "application/json");
        conn.setDoOutput(true);
        conn.setDoInput(true);
        // 设置不用缓存
        conn.setUseCaches(false);
        //权限
        conn.setRequestProperty("Authorization", " Bearer fc58be57c46b32f9a2c32e5393684ac0");
        
         // 开始连接请求
        conn.connect();
        OutputStream  out = conn.getOutputStream();     
        // 写入请求的字符串
        out.write((str).getBytes());
        out.flush();
        out.close();
        
        // 请求返回的状态
        if (conn.getResponseCode() == 200) {
            System.out.println("连接成功");
            // 请求返回的数据
            InputStream in = conn.getInputStream();
            String a = null;
            try {
                byte[] data1 = new byte[in.available()];
                in.read(data1);
                // 转成字符串
                a = new String(data1);
                System.out.println(a);
            } catch (Exception e1) {
                // TODO Auto-generated catch block
                e1.printStackTrace();
            }
        } else {
            System.out.println(conn.getResponseCode()+":no++");
        }

    }
    public static void main(String[] args) throws Exception {//地址
        String url = "http://...";
        //查询参数
        String str = "{\"ids\":[15410,15402]}";
        readParse(url,str);
    }
}