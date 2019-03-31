
public class LoanJFrame extends JFrame implements ActionListener
{
	private JtextField texts[];
	private JSpinner spin_year,spin_month;
	private JButton button;
	private DefaultTableModel tableModel;
	
	public LoanJFrame()
	{
		super("hehe");
		this.setBounds(300,240,780,400);

		JPanel panel = new JPanle();
		this.add(panel,"North");
		String str[] = {"贷款金额","元 贷款利息","%月 贷款年限","年 其实年月","年","月"};
		String str_text[] = {"100000","0.5025","5"};

		this.texts = new JTextField[str_text.length];
		int i = 0;
		for(int i = 0 ;i < str_text.length;i++)
		{
			panel.add(new Lable(str[i]));
			this.texts[i] = new JTextField(str_text[i],6);
			panel.add(this.texts[i]);
		}
		for(;i<str.length;i++)
			panel.add(new JLable(str[i]));

		Calendar today = Calendar.getInstance();
		int year = today.get(Calendar.YEAR);

		int nextMonth = today.get(Calendar.MONTH) + 1;
		nextMonth = nextMonth%12 + 1;
		if(nextMonth == 1)
			year++;
		spin_year = new JSpinner();
		spin_year.setValue(year);
		panel.add(spin_year,7);

		spin_month = new JSpinner(new SpinnerNumberModel(nextmonth,1,12,1));

		panel.add(spin_month,9);

		this.button = new JButton("计算");
		panel.add(button);
		button.addActionListener(this);

		String titles[] = {"年月","本金金额(元)","月还本金(元)","月还利息(元)","月还本息(元)"};
		this.tablemodel = new DefaultTableModel(titles,0);
		JTable itable = new JTable();
		this.add(new ScrollPane(jtable));
	}
	public void actionPerformed(ActionEvent ev)
	{
		int  month = Integer.parseInt(texts[2].getText())*12;
		int year = Integer.parseInt("" + spin_year.getValue());
		int mon = Integer.parseInt("" + spin_month.getValue());
		double leavings = Double.parseDouble("" + texts[0].getText());
		double pay = leavings/months;
		double rate = Double.parseDouble("" + texts[1].getText());

		this.tablemodel.setRowCount(months);

		for(int i = 0;i < months;i++)
		{
			this.tablemodel.setValueAt(year+"年"+mon+"月"，i,0);
			this.tablemodel.setValueAt(String.format("%9.2f",leavings),i,1);
			this.tablemodel.setValueAt(String.format("%9.2f",pay),i,2);
			this.tablemodel.setValueAt(String.format("%9.2f",leavings*rate*0.01),i,3);
			this.tablemodel.setValueAt(String.format("%9.2f",pay+leavings*rate*0.01),i,4);

			if(mon == 12)
				year ++;
			mon = mon%12 + 1;
			leavings -= pay;
		}
	}
}
