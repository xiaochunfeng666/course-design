import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;

public class LibraryManagementSystemGUI extends  JFrame {
    //初始化数组
    // myBooks是存储对象的数组
    private Book[] myBooks = new Book[600];
    private int bookCount = 0;
    //读取文件
    private static final String FILENAME = "D:\\code_Java\\course design\\books.docx";

    //主界面
    public LibraryManagementSystemGUI() {
        // 读取已有书籍信息
        readBooksFromFile(FILENAME);

        //主菜单
        setTitle("图书管理系统");
        setSize(400, 300);
        setLocation(300, 250);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        JPanel menuPanel = new JPanel();
        menuPanel.setLayout(new GridLayout(5, 2));
        JLabel welcomeLabel = new JLabel("欢迎使用图书管理系统");
        menuPanel.add(welcomeLabel);

        String[] options = {"录入", "修改", "查询", "删除", "借阅", "还书", "退出"};
        for (String option : options) {
            JButton button = new JButton(option);
            button.addActionListener(new MenuButtonListener());
            menuPanel.add(button);
        }

        add(menuPanel, BorderLayout.WEST);
    }

    // 从文件中读取书籍信息并存入myBooks数组
    private void readBooksFromFile(String fileName) {
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            String line;

            // 数组索引
            int index = 0;

            while ((line = br.readLine()) != null) {

                // 假设文件每行的格式为：title\tauthor\tpublisher\tnumber\tlender\tlend
                String[] parts = line.split("\t");

                if (parts.length >= 6) {
                    String title = parts[0].trim();
                    String author = parts[1].trim();
                    String publisher = parts[2].trim();
                    int number = Integer.parseInt(parts[3].trim());
                    boolean lend = Boolean.parseBoolean(parts[5].trim());
                    String lender = parts[4].trim();

                    // 创建Book对象并存入数组
                    myBooks[index] = new Book();
                    myBooks[index].title.setText(title);
                    myBooks[index].author.setText(author);
                    myBooks[index].publisher.setText(publisher);
                    myBooks[index].number.setText(String.valueOf(number));
                    myBooks[index].lender.setText(lender);
                    myBooks[index].lend.setSelected(lend);

                    // 移动到下一个索引位置
                    index++;
                    bookCount++;
                }
            }
        } catch (IOException | NumberFormatException e) {
            e.printStackTrace();
        }
    }

    // 将书籍信息写入文件
    private void writeBooksToFile(String fileName) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(fileName))) {
            for (int i = 0; i < bookCount; ++i) {
                if (myBooks[i] != null) {
                    String title = myBooks[i].title.getText().trim();
                    String author = myBooks[i].author.getText().trim();
                    String publisher = myBooks[i].publisher.getText().trim();
                    String number = myBooks[i].number.getText().trim();
                    String lender = myBooks[i].lender.getText().trim();
                    String lend = String.valueOf(myBooks[i].lend.isSelected());

                    // 将书籍信息以逗号分隔的格式写入文件
                    String line = title + "\t" +
                            author + "\t" +
                            publisher + "\t" +
                            number + "\t" + lender +
                            "\t";
                    if(lend == "false"){
                        lend = "未借阅";
                    } else {
                        lend = "已借阅";
                    }

                    line += lend;
                    bw.write(line);
                    bw.newLine(); // 写入换行符
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private class MenuButtonListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String command = e.getActionCommand();
            switch (command) {
                case "录入":
                    String inPut = JOptionPane.showInputDialog(LibraryManagementSystemGUI.this,
                            "请输入需要录入的书籍数量");
                    if (inPut != null && !inPut.isEmpty()) {
                        int count = Integer.parseInt(inPut);

                        // 根据用户输入的数量录入书籍
                        for (int i = 0; i < count; i++) {
                            if (bookCount < myBooks.length) {

                                //创建Book对象并且将其添加到主界面中
                                myBooks[bookCount] = new Book();
                                BookInfo bookInfo = myBooks[bookCount].getBookInfoDialog(LibraryManagementSystemGUI.this);
                                if (bookInfo != null) {
                                    bookCount++;
                                    JOptionPane.showMessageDialog(LibraryManagementSystemGUI.this,
                                            "成功录入1本书籍");
                                } else {
                                    JOptionPane.showMessageDialog(LibraryManagementSystemGUI.this,
                                            "录入取消或未完成");
                                    break;
                                }
                            } else {
                                JOptionPane.showMessageDialog(LibraryManagementSystemGUI.this,
                                        "书籍数量已达上限");
                                break;
                            }
                        }
                    } else {
                        JOptionPane.showMessageDialog(LibraryManagementSystemGUI.this,
                                "未输入数量");
                    }
                    break;

                case "修改":
                    String modify = JOptionPane.showInputDialog(LibraryManagementSystemGUI.this,
                            "请输入需要修改的书籍数量");
                    if (modify != null && !modify.isEmpty()) {
                        int count3 = Integer.parseInt(modify);
                        for (int i = 0; i < count3; i++) {
                            String numStr = JOptionPane.showInputDialog(LibraryManagementSystemGUI.this,
                                    "请输入要修改的书籍编号:");
                            if (numStr != null && !numStr.isEmpty()) {
                                Book.modifyBook(LibraryManagementSystemGUI.this, myBooks, numStr);
                            } else {
                                JOptionPane.showMessageDialog(LibraryManagementSystemGUI.this,
                                        "未选择要修改的书籍");
                            }
                        }
                    }
                    break;

                case "查询":
                    Book.searchBook(LibraryManagementSystemGUI.this, myBooks);
                    break;

                case "删除":
                    String delete = JOptionPane.showInputDialog(LibraryManagementSystemGUI.this,
                            "请输入需要删除的书籍数量");
                    if (delete != null && !delete.isEmpty()) {
                        int count2 = Integer.parseInt(delete);
                        for (int i = 0; i < count2; i++) {
                            String numStr = JOptionPane.showInputDialog(LibraryManagementSystemGUI.this,
                                    "请输入要删除的书籍编号:");
                            if (numStr != null && !numStr.isEmpty()) {
                                Book.deleteBook(LibraryManagementSystemGUI.this,
                                        numStr, myBooks);
                            } else {
                                JOptionPane.showMessageDialog(LibraryManagementSystemGUI.this,
                                        "未选择要删除的书籍");
                            }
                        }
                    }
                    break;

                case "借阅":
                    String borrow = JOptionPane.showInputDialog(LibraryManagementSystemGUI.this,
                            "请输入需要借阅的书籍数量");
                    if (borrow != null && !borrow.isEmpty()) {
                        int count4 = Integer.parseInt(borrow);
                        for (int i = 0; i < count4; i++) {
                            String numStr = JOptionPane.showInputDialog(LibraryManagementSystemGUI.this,
                                    "请输入要借阅的书籍编号:");
                            if (numStr != null && !numStr.isEmpty()) {
                                int n = Book.findBookByNumber(numStr, myBooks);
                                if (n != -1 && !myBooks[n].lend.isSelected()) {
                                    myBooks[n].lend.setSelected(true);
                                    String name = JOptionPane.showInputDialog(LibraryManagementSystemGUI.this,
                                            "请输入借阅人姓名");
                                    myBooks[n].lender.setText(name);
                                    JOptionPane.showMessageDialog(LibraryManagementSystemGUI.this,
                                            "书籍借阅成功！",
                                            "借阅成功", JOptionPane.INFORMATION_MESSAGE);
                                } else {
                                    JOptionPane.showMessageDialog(LibraryManagementSystemGUI.this,
                                            "无效的书籍编号",
                                            "借阅失败", JOptionPane.ERROR_MESSAGE);
                                }
                            } else {
                                JOptionPane.showMessageDialog(LibraryManagementSystemGUI.this,
                                        "未选择要借阅的书籍");
                            }
                        }
                    }
                    break;

                case "还书":
                    String returnBook = JOptionPane.showInputDialog(LibraryManagementSystemGUI.this,
                            "请输入需要归还的书籍数量");
                    if (returnBook != null && !returnBook.isEmpty()) {
                        int count5 = Integer.parseInt(returnBook);
                        for (int i = 0; i < count5; i++) {
                            String numStr = JOptionPane.showInputDialog(LibraryManagementSystemGUI.this,
                                    "请输入要归还的书籍编号:");
                            if (numStr != null && !numStr.isEmpty()) {
                                int n = Book.findBookByNumber(numStr, myBooks);
                                if (n != -1 && myBooks[n].lend.isSelected()) {
                                    myBooks[n].lend.setSelected(false);
                                    myBooks[n].lender.setText(null);
                                    JOptionPane.showMessageDialog(LibraryManagementSystemGUI.this,
                                            "书籍归还成功！",
                                            "归还成功", JOptionPane.INFORMATION_MESSAGE);
                                } else {
                                    JOptionPane.showMessageDialog(LibraryManagementSystemGUI.this,
                                            "无效的书籍编号",
                                            "归还失败", JOptionPane.ERROR_MESSAGE);
                                }
                            } else {
                                JOptionPane.showMessageDialog(LibraryManagementSystemGUI.this,
                                        "未选择要归还的书籍");
                            }
                        }
                    }
                    break;

                case "退出":
                    writeBooksToFile(FILENAME);
                    System.exit(0);
                    break;

                default:
                    break;
            }
        }
    }
}