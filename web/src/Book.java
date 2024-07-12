import javax.swing.*;
import java.awt.*;

public class Book extends JPanel {

    public JTextField title;
    public JTextField author;
    public JTextField publisher;
    public JTextField number;
    public JTextField lender;
    public JCheckBox lend;

    //构造函数
    public Book() {
        //设置布局
        setLayout(new GridLayout(0, 2));

        //创建组件并且加入到面板中
        JLabel titleLabel = new JLabel("书名:");
        title = new JTextField(20);
        add(titleLabel);
        add(title);

        JLabel authorLabel = new JLabel("作者:");
        author = new JTextField(20);
        add(authorLabel);
        add(author);

        JLabel publisherLabel = new JLabel("出版社:");
        publisher = new JTextField(20);
        add(publisherLabel);
        add(publisher);

        JLabel numberLabel = new JLabel("编号:");
        number = new JTextField(20);
        add(numberLabel);
        add(number);

        JLabel lenderLabel = new JLabel("借书人:");
        lender = new JTextField(20);
        add(lenderLabel);
        add(lender);

        lend = new JCheckBox("借阅状态");
        add(lend);
    }

    // 录入书籍信息，获取书籍信息并返回
    public BookInfo getBookInfoDialog (Component parentComponent) {
        int result = JOptionPane.showConfirmDialog(parentComponent,this, "请输入书籍信息",  JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
        if (result == JOptionPane.YES_OPTION) {
            return new BookInfo(
                    title.getText(),
                    author.getText(),
                    publisher.getText(),
                    Integer.parseInt(number.getText()),
                    lend.isSelected(),
                    lender.getText()
            );
        }

        // 用户取消录入，返回null
        return null;
    }

    //删除书籍
    public static void deleteBook(Component parentComponent, String bookNumber, Book[] myBooks) {
        //寻找索引
        int bookIndex = findBookByNumber(bookNumber, myBooks);
        if (bookIndex >= 0 && bookIndex < myBooks.length) {
            Book bookToDelete = myBooks[bookIndex];

            //判断是否处于借阅状态
            if (bookToDelete != null && bookToDelete.lend.isSelected()) {
                JOptionPane.showMessageDialog(parentComponent, "该书籍处于借阅状态，不能删除！", "无法删除", JOptionPane.ERROR_MESSAGE);
            } else {
                int confirm = JOptionPane.showConfirmDialog(parentComponent, "确定删除书籍？", "确认删除", JOptionPane.YES_NO_OPTION);
                if (confirm == JOptionPane.YES_OPTION) {

                    //用null来代表是否删除
                    myBooks[bookIndex] = null;
                    JOptionPane.showMessageDialog(parentComponent, "书籍删除成功！", "删除成功", JOptionPane.INFORMATION_MESSAGE);
                }
            }
        } else {
            JOptionPane.showMessageDialog(parentComponent, "无效的书籍编号", "删除失败", JOptionPane.ERROR_MESSAGE);
        }
    }

    //修改
    public static void modifyBook(Component parentComponent, Book[] myBooks, String num) {
        // 创建一个面板用于显示书籍信息的输入框和复选框
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(0, 2));

        JTextField titleField = new JTextField(20);
        JTextField authorField = new JTextField(20);
        JTextField publisherField = new JTextField(20);
        JTextField numberField = new JTextField(20);
        JTextField lenderField = new JTextField(20);
        JCheckBox lendCheckBox = new JCheckBox("借阅状态");

        panel.add(new JLabel("书名:"));
        panel.add(titleField);
        panel.add(new JLabel("作者:"));
        panel.add(authorField);
        panel.add(new JLabel("出版社:"));
        panel.add(publisherField);
        panel.add(new JLabel("编号:"));
        panel.add(numberField);
        panel.add(new JLabel("借阅者:"));
        panel.add(lenderField);
        panel.add(lendCheckBox);

        //获取索引
        int bookIndex = findBookByNumber(num, myBooks);
        if(bookIndex != -1) {

            Book bookToUpdate = myBooks[bookIndex];

            // 显示一个确认对话框，允许用户输入新的书籍信息或选择借阅状态
            int result = JOptionPane.showConfirmDialog(parentComponent, panel, "修改书籍信息", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
            if (result == JOptionPane.YES_OPTION) {
                // 获取用户输入的信息
                String newTitle = titleField.getText();
                String newAuthor = authorField.getText();
                String newPublisher = publisherField.getText();
                String newNumber = numberField.getText();
                String newLender = lenderField.getText();
                boolean isLend = lendCheckBox.isSelected();

                // 更新书籍信息
                bookToUpdate.title.setText(newTitle);
                bookToUpdate.author.setText(newAuthor);
                bookToUpdate.publisher.setText(newPublisher);
                bookToUpdate.number.setText(newNumber);
                bookToUpdate.lender.setText(newLender);
                bookToUpdate.lend.setSelected(isLend);

                JOptionPane.showMessageDialog(parentComponent, "书籍信息已成功修改！", "修改成功", JOptionPane.INFORMATION_MESSAGE);
            } else {
                JOptionPane.showMessageDialog(parentComponent, "未修改书籍信息", "取消修改", JOptionPane.INFORMATION_MESSAGE);
            }
        } else {
            JOptionPane.showMessageDialog(parentComponent, "未找到编号为 " + num + " 的书籍", "修改失败", JOptionPane.ERROR_MESSAGE);
        }
    }


    // 辅助方法：通过书籍编号查找书籍在数组中的索引
    public static int findBookByNumber(String bookNumber, Book[] myBooks) {
        for (int i = 0; i < myBooks.length; i++) {
            if (myBooks[i] != null && myBooks[i].number.getText().equals(bookNumber)) {
                return i; // 找到对应编号的书籍，返回索引
            }
        }
        return -1; // 未找到对应编号的书籍
    }

    //查询
    public static void searchBook(Component parentComponent, Book[] myBooks) {
        String[] options = {"查询所有书籍", "查询所有借阅书籍", "查询所有未借阅书籍", "查询指定书籍"};
        int choice = JOptionPane.showOptionDialog(parentComponent,
                "请选择查询类型：",
                "查询书籍",
                JOptionPane.YES_NO_CANCEL_OPTION,
                JOptionPane.QUESTION_MESSAGE,
                null,
                options,
                options[3]);

        switch (choice) {
            case 0:
                // 查询所有书籍
                displaySearchResults("所有书籍", getAllBooksInfo(myBooks));
                break;
            case 1:
                // 查询所有借阅书籍
                displaySearchResults("所有借阅书籍", getBorrowedBooksInfo(myBooks));
                break;
            case 2:
                // 查询所有未借阅书籍
                displaySearchResults("所有未借阅书籍", getAvailableBooksInfo(myBooks));
                break;
            case 3:
                // 查询指定书籍
                String searchTerm = JOptionPane.showInputDialog(parentComponent, "请输入要查询的书籍编号：");
                if (searchTerm != null && !searchTerm.isEmpty()) {
                    int m = findBookByNumber(searchTerm, myBooks);
                    if (m != -1) {
                        Book book = myBooks[m];
                        BookInfo bookInfo = new BookInfo(book.title.getText(), book.author.getText(),
                                book.publisher.getText(), Integer.parseInt(book.number.getText()),
                                book.lend.isSelected(), book.lender.getText());
                        JOptionPane.showMessageDialog(parentComponent,
                                "查询结果：\n" + bookInfo.toString(),
                                "查询结果",
                                JOptionPane.INFORMATION_MESSAGE);
                    } else {
                        JOptionPane.showMessageDialog(parentComponent, "无效的书籍编号",
                                "查询失败",
                                JOptionPane.ERROR_MESSAGE);
                    }
                }
                break;
            case JOptionPane.CLOSED_OPTION:
                // 取消选择
                break;
        }
    }

    // 获取所有书籍信息的方法
    private static String getAllBooksInfo(Book[] myBooks) {
        StringBuilder info = new StringBuilder();
        for (Book book : myBooks) {
            if(book == null){
                continue;
            }
            BookInfo bookInfo = new BookInfo(book.title.getText(), book.author.getText(),
                    book.publisher.getText(), Integer.parseInt(book.number.getText()),
                    book.lend.isSelected(), book.lender.getText());
            info.append(bookInfo.toString()).append("\n");
        }
        return info.toString();
    }

    // 获取所有借阅书籍信息的方法
    private static String getBorrowedBooksInfo(Book[] myBooks) {
        StringBuilder info = new StringBuilder();
        for (Book book : myBooks) {
            if (book != null && book.lend.isSelected()) {
                BookInfo bookInfo = new BookInfo(book.title.getText(), book.author.getText(),
                        book.publisher.getText(), Integer.parseInt(book.number.getText()),
                        book.lend.isSelected(), book.lender.getText());
                info.append(bookInfo.toString()).append("\n");
            }
        }
        return info.toString();
    }

    // 获取所有未借阅书籍信息的方法
    private static String getAvailableBooksInfo(Book[] myBooks) {
        StringBuilder info = new StringBuilder();
        for (Book book : myBooks) {
            if (book != null && !book.lend.isSelected()) {
                BookInfo bookInfo = new BookInfo(book.title.getText(), book.author.getText(),
                        book.publisher.getText(), Integer.parseInt(book.number.getText()),
                        book.lend.isSelected(), book.lender.getText());
                info.append(bookInfo.toString()).append("\n");
            }
        }
        return info.toString();
    }

    // 显示查询结果的方法
    private static void displaySearchResults(String title, String results) {

        JTextArea textArea = new JTextArea(results);

        // 设置为不可编辑
        textArea.setEditable(false);

        // 创建一个JScrollPane来包装JTextArea，并设置滚动条始终可见
        JScrollPane scrollPane = new JScrollPane(textArea);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);

        // 创建一个自定义的JDialog来显示结果
        JDialog dialog = new JDialog();
        dialog.setTitle("查询结果：" + title);
        dialog.setModal(true);

        // 创建一个内容面板，并设置布局
        JPanel contentPane = new JPanel(new BorderLayout());
        contentPane.add(scrollPane, BorderLayout.CENTER);

        // 设置对话框的大小和位置
        dialog.setSize(new Dimension(400, 300));
        dialog.setLocationRelativeTo(null);

        // 将内容面板添加到对话框中
        dialog.setContentPane(contentPane);

        // 显示对话框
        dialog.setVisible(true);
    }
}

//获取信息的类
class BookInfo{
    private String title;
    private String author;
    private String publisher;
    private int number;
    private boolean lend;
    private String lender;

    public BookInfo(String title, String author, String publisher, int number, boolean lend, String lender) {
        this.title = title;
        this.author = author;
        this.publisher = publisher;
        this.number = number;
        this.lend = lend;
        this.lender = lender;
    }

    @Override
    public String toString() {
        boolean f = lend ? true : false;
        String x = "未借阅";
        if(f){
            x = "已借阅";
        }
        return "书名: " + title + "\n" +
                "作者: " + author + "\n" +
                "出版社: " + publisher + "\n" +
                "编号: " + number + "\n" +
                "借阅状态: " + x + "\n" +
                "借书人: " + lender + "\n";

    }
}