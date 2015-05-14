import java.awt.Button;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.lang.reflect.Field;
import java.util.LinkedList;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

import org.omg.CosNaming.IstringHelper;
class Point{
	int x, y;

	public double getX() {
		return x;
	}
	public void setX(int x) {
		this.x = x;
	}
	public double getY() {
		return y;
	}
	public void setY(int y) {
		this.y = y;
	}
	public Point() {
		// TODO Auto-generated constructor stub
		x = 0;
		y = 0;
	}
	public Point(int x, int y) {
		super();
		this.x = x;
		this.y = y;
	}
	void setLocation(int x, int y){
		this.x = x;
		this.y = y;
	}
	
}
public class JSQ extends JFrame{
	static LinkedList<String> List = new LinkedList<String>();
	static LinkedList<Float>  numbers = new LinkedList<Float>();
	static LinkedList<Point> kuohao = new LinkedList<Point>();
//	static boolean alreadypoint = false;
	JButton clear, chexiao, lkuohao, rkuohao;
	JButton jia,jian,cheng, chu, equals;
	JButton  number[];//one, two, tree, four, five, six, seven, eight, nine, zero;
	JButton point;
	JButton button[];
	JTextField field;
	MouseListener listener[];
	static String strings;
    class Adapter extends MouseAdapter{
    	String str;
    	public Adapter(JButton button) {
	    	// TODO Auto-generated constructor stub
    		str = button.getText();
    		System.out.println(str);
    	}
    	/**
    	 * 判断是否是数字
    	 * @param laststr
    	 * @return
    	 */
    	private boolean isnumber(String laststr){
    		if(laststr.equalsIgnoreCase("0") || laststr.equalsIgnoreCase("1") || laststr.equalsIgnoreCase("2") ||
    				laststr.equalsIgnoreCase("3") || laststr.equalsIgnoreCase("4") || laststr.equalsIgnoreCase("5") ||
    				laststr.equalsIgnoreCase("6") || laststr.equalsIgnoreCase("7") || laststr.equalsIgnoreCase("8") || 
    				laststr.equalsIgnoreCase("9")){
    			return true;
    		}
    		else return false;
    		
    	}
    	/**
    	 * 判断是否已经有了小数点
    	 * @return
    	 */
    	private boolean isalreadypoint(){
    		int i = 0;
         	if(List.size()>0){
    	    	for(i = List.size() - 1; i >= 0; i--){
    		    	if(! isnumber(List.get(i))){
    			    	break;
         			}
        		}
    	    	if(i >= 0){
        	    	if(List.get(i).equalsIgnoreCase(".")){
         		    	return true;
            		}
            		else
        	    		return false;
              	}
    	    	else return false;
    		}
    		else
    			return false;
    		
    	}
/**
	 * 判断是否为空字符    	
	 */
	private boolean isnull(String laststr){
		if(laststr.equalsIgnoreCase("") ){
			return true;
		}
		return false;
	}
    	/**
    	 * 判断是否为运算符
    	 * @param laststr
    	 * @return
    	 */
    	private boolean isyunsuanfu(String laststr){
    		if(laststr.equalsIgnoreCase("+")  || laststr.equalsIgnoreCase("-")  || laststr.equalsIgnoreCase("*") || laststr.equalsIgnoreCase("/") ){
    			return true;
    		}
    		return false;
    	}
    	/**
    	 * 判断是否是一级运算符
    	 * @param laststr
    	 * @return
    	 */
    	private boolean is1yunsuanfu(String laststr){
    		if(laststr.equalsIgnoreCase("+") || laststr.equalsIgnoreCase("-") ){
    			return true;
    		}
    		return false;
    	}
    	/**
    	 * 判断是否为二级运算符
    	 * @param laststr
    	 * @return
    	 */
    	private boolean is2yunsuanfu(String laststr){
    		if(laststr.equalsIgnoreCase("*") || laststr.equalsIgnoreCase("/") ){
    			return true;
    		}
    		return false;
    	}
    	/**
    	 * 判断是否为左括号
    	 * @param laststr
    	 * @return
    	 */
     	private boolean isL(String laststr){
     		if(laststr.equalsIgnoreCase("("))return true;
     		return false;
     	}
     	/**
     	 * 判断是否为右括号
     	 * @param laststr
     	 * @return
     	 */
     	private boolean isR(String laststr){
     		if(laststr.equalsIgnoreCase(")"))return true;
     		return false;
     	}
     	private boolean ishasL(){
     		int i = 0,L = 0, R = 0;
    		for(i = 0; i < List.size(); i++){
    			if(List.get(i) == "(")
    				L++;
    			if(List.get(i) ==")")
    				R++;
    		}
    		if(L>R)
        		return true;
    		else
    			return false;
    	}
        private boolean ispoint(String laststr){
    		if(laststr.equalsIgnoreCase("."))return true;
    		return false;
    	}
        private boolean numberOK(String laststr){
    		if(isnull(laststr)||isyunsuanfu(laststr)||isL(laststr)||isnumber(laststr)||ispoint(laststr))return true;
    		return false;
    	}
        private boolean pointOK(String laststr){
    		if(isnumber(laststr)&&!isalreadypoint())return true;
    		return false;
    	}
        private boolean LOK(String laststr){
    		if(isnull(laststr)||isyunsuanfu(laststr)||isL(laststr))return true;
    		return false;
    	}
        private boolean ROK(String laststr){
    		if((isnumber(laststr)||isR(laststr))&&ishasL())return true;
    		return false;
    	}
        private boolean yiyusuanfuOK(String laststr){
    		if(isnull(laststr)||isnumber(laststr)||isL(laststr)||isR(laststr))
    			return true;
    		return false;
    	}
        private boolean eryusuanfuOK(String laststr){
    		if(isnumber(laststr)||isR(laststr))return true;
    		return false;
    	}
        private String getlaststr(){
        	if(List.size() == 0)
        		return "";
        	return List.getLast();
        }
        private String getAllstr(){
        	String string = "";
        	for (int i = 0; i < List.size(); i++) {
				string += List.get(i);
			}
        	return string;
        }
        private boolean isclear(String laststr){
    		if(laststr.equalsIgnoreCase("clear"))
    			return true;
    		return false;
    	}
        private boolean ischexiao(String laststr){
    		if(laststr.equalsIgnoreCase("撤销"))
    			return true;
    		return false;
    	}
        private boolean isequals(String laststr){
      		if(laststr.equalsIgnoreCase("="))
    			return true;
    		return false;
        }
        private int getLnum(int begin,int last){
        	int num = 0;
        	for(int i = begin; i < last; i++){
        		if(List.get(i) == "("){
        			num++;
        		}
        	}
        	return num;
        }
        private float getresult(int begin,int end){
        	//初始化
        	LinkedList numb = new LinkedList();
        	String yunsuanfu1 = "";
        	String temp = "";
        	int i = begin;
        	int y = end;
        	Point p = new Point();
        	String float1 = "";
        	int Lcounter = 0,Rcounter = 0;
        	//在这个域里面（begin，end）
        	while(i < y){//大循环里面
        		temp = List.get(i);
        	if(Lcounter == 0){//如果还没有遇见过括号        		
        		if(is1yunsuanfu(temp) && i == begin){
                	numb.add(Float.valueOf("0"));
				    numb.add(temp);
        			i++;
        		}
				else if(is2yunsuanfu(temp)){
				    numb.add(temp);
					i++;
				}
				else if(is1yunsuanfu(temp)){
					numb.add(temp);
					i++;
				}
        		if(i < y){//刷新temp
        			temp = List.get(i);
        		}      		
        		while(isnumber(temp)||ispoint(temp)){//将里面的数字给提取出来
        			float1 += temp;
        			i++;
        			if(i < y){
            			temp = List.get(i);System.out.println("shuz:"+temp);
            		}
        			
        			else break;
        		}
        		if(float1 != ""){//如果数字不为空的话，就加入这个容器中      			
        			numb.add(Float.valueOf(float1).floatValue());//找到一个数字
        			System.out.println(float1);
        			float1 = "";
        			yunsuanfu1 = "";
        		}
        		
//        		if(isyunsuanfu(temp)){
//        			numb.add(temp);
//        			i++;
//        			if(i < y){
//            			temp = List.get(i);
//            		} 
//        		}
         	}
        		if(isL(temp)){       			
        			if(Lcounter == 0){
        				p.setX(i);
        				System.out.println("begin :"+i);
        			}
        			Lcounter++;     			
        			i++;
        		}
        		else if(isR(temp)){
        			Rcounter++;
        			if(Rcounter == Lcounter && Lcounter != 0){
        				p.setY(i); 
           				System.out.println("end :"+i);
        				numb.add(getresult(p.x+1, p.y));
        				Lcounter = Rcounter = 0;
        			}        			
        			i++;
        		} 
        		else 
        		{
        			if(Lcounter != 0){
        	    		i++;
        	    	}	
        		}
        	}
        	
        	
        	
        	
        	float temp1, temp3, temp5;
        	String temp2, temp4;
	    		System.out.println("size :"+ numb.size());       	
        	while(true){
        		if(numb.size() == 0)
        			return 0;
        		if(numb.size() == 1){
   		    		System.out.println("size :"+ numb.size());
        			return temp1 = (float) numb.getFirst();
        		}
        		if(numb.size() == 3){
        			System.out.println("size :"+ numb.size());
             		temp1 = (float) numb.get(0);
            		temp2 = (String) numb.get(1);
             		temp3 = (float) numb.get(2); 
             		if(temp2 == "+"){
        				temp1 = temp1 + temp3;
        			}     			
        			if(temp2 == "-"){
        				temp1 = temp1 - temp3;
        			}
        			if(temp2 == "*"){
        				temp1 = temp1 * temp3;
        			}     			
        			if(temp2 == "/"){
        				temp1 = temp1 / temp3;
        			}
   		    		
        			return temp1;
        		}
        		if(numb.size() >= 5){
        			System.out.println("size :"+ numb.size());
             		temp1 = (float) numb.get(0);
            		temp2 = (String) numb.get(1);
             		temp3 = (float) numb.get(2);
            		temp4 = (String) numb.get(3);
            		temp5 = (float) numb.get(4);
            		if(is1yunsuanfu(temp2) && is2yunsuanfu(temp4)){
            			if(temp4 == "*"){
            				temp3 = temp3*temp5;
            				System.out.println("temp3: "+temp3);
            			}           			
            			else if(temp4 == "/"){
            				temp3 = temp3/temp5;
            				System.out.println("temp3: "+temp3);
            			}            				
            			numb.set(2, temp3);//去掉temp3赋值给第3位
            			numb.remove(3);//去掉temp4 和temp5
            			numb.remove(3);      		    		
            		}
            		else{
            			if(temp2 == "+"){
            				temp1 = temp1 + temp3;
            			}     			
            			if(temp2 == "-"){
            				temp1 = temp1 - temp3;
            			}   
            			if(temp2 == "*"){
            				temp1 = temp1 * temp3;
            			}     			
            			if(temp2 == "/"){
            				temp1 = temp1 / temp3;
            			} 
            			System.out.println("temp1:" + temp1);
            			numb.set(0, temp1);
            			numb.set(1, temp4);//把temp4赋值给第2位，把temp5赋值给第3位
            			numb.set(2, temp5);
    	    			numb.remove(3);
    		    		numb.remove(3);
            		}
        		}        		
        	}
//        	return 0;
        }
        private void xiubu(){
        	int Lcounter = 0, Rcounter = 0;
        	String temp = "";
        	for(int i = 0; i < List.size(); i++){
        		temp = List.get(i);
	    		if(isL(temp )){
        			Lcounter++;
        		}
         		else if(isR(temp)){
         			Rcounter++;
        		}
    		}
        	while(Lcounter > Rcounter){
        		List.addLast(")");
        		Rcounter++;
        	}
        }
        @Override
        public void mouseClicked(MouseEvent e) {
//        	super.mouseClicked(e);
        	String laststr = getlaststr();
        	if(isnumber(str)){
        		if(numberOK(laststr)){
        			List.add(str);
           			strings += str;
//        			return;
        		}
        	}
        		
        	else if(ispoint(str)){
        		if(pointOK(laststr)){
        			List.add(str);
           			strings += str;
//        			return;
        		}
        	}
        		
        	else if(isL(str)){
        		if(LOK(laststr)){
        			List.add(str);
           			strings += str;
//        			return;
        		}
        	}
        	else if(isR(str)){
        		if(ROK(laststr)){
        			List.add(str);
           			strings += str;
//        			return;
        		}
        	}
        	else if(is1yunsuanfu(str)){
        		if(yiyusuanfuOK(laststr)){
        			List.add(str);
           			strings += str;
//        			return;
        		}
        	}
        	else if(is2yunsuanfu(str)){
        		if(eryusuanfuOK(laststr)){
        			List.add(str);
        			strings += str;
//        			return;
        		}
        	} 
        	else if(isclear(str)){
        		List.clear();
        	}
        	else if(ischexiao(str)){
        		if(!List.isEmpty())
            		List.removeLast();
        	}
        	else if(isequals(str)){
        		if(!(isnumber(getlaststr())||isR(getlaststr()))){
        			field.setText("出错！！！");
        			return;
        		}
        		xiubu();
        		field.setText(getAllstr()+" = "+getresult(0,List.size()));
        		List.clear();
        		return;
        	}
        	field.setText(getAllstr());
        }
    }

	
	public JSQ() {
		// 初始化
		super("计算器");
		field = new JTextField(30);
		button = new JButton[20];
		number = new JButton[10];
		for( int i = 0; i < 10; i++){
			button[i] = number[i] = new JButton(i+"");
		}
		button[10] = clear = new JButton("clear");
		button[11] = chexiao = new JButton("撤销");
		button[12] = lkuohao = new JButton("(");
		button[13] = rkuohao = new JButton(")");
		button[14] = point = new JButton(".");
		button[15] = jian = new JButton("-");
		button[16] = cheng = new JButton("*");
		button[17] = chu = new JButton("/");
		button[18] = jia = new JButton("+");
		button[19] = equals = new JButton("=");
		listener = new MouseListener[20];
	}
	private void addaction(){
		int i = 0;	
		for(i = 0; i < 20; i++){
			listener[i] = new Adapter(button[i]);
	    	button[i].addMouseListener(listener[i]);
		}
	}
	void run(){
		addaction();
		setSize(350, 200);
		setResizable(false);//固定计算器的大小
		field.setEditable(false);
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		JPanel jp2 = new JPanel(new GridLayout(4, 5));
		for(int i = 0; i < 20; i++){
			jp2.add(button[i]);
		}
		JPanel jp1 = new JPanel(new FlowLayout());
		jp1.add(field);
		jp1.add(jp2);
		add(jp1);
	}
	public static void main(String[] args) {
		JSQ J = new JSQ();
		J.run();
	}
}
