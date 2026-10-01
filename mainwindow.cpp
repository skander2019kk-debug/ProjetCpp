#include "mainwindow.h"
#include <QtWidgets>
#include <QPainterPath>

namespace {
QIcon icon(const QString &kind, QColor color = QColor("#074778"))
{
    QPixmap pix(48,48); pix.fill(Qt::transparent);
    QPainter p(&pix); p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(color, 3.2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    if (kind == "person" || kind == "people") {
        p.setBrush(color); p.setPen(Qt::NoPen);
        if (kind == "people") { p.drawEllipse(QRectF(2,13,10,10)); p.drawRoundedRect(QRectF(0,25,14,17),5,5); p.drawEllipse(QRectF(36,13,10,10)); p.drawRoundedRect(QRectF(34,25,14,17),5,5); }
        p.drawEllipse(QRectF(15,3,18,18)); p.drawRoundedRect(QRectF(10,24,28,21),8,8);
    } else if (kind == "eye") { p.drawEllipse(QRectF(4,13,40,22));p.setBrush(color);p.drawEllipse(QRectF(18,18,12,12));
    } else if (kind == "search") { p.drawEllipse(QRectF(5,4,27,27)); p.drawLine(29,29,43,43);
    } else if (kind == "plus") { p.drawLine(24,7,24,41); p.drawLine(7,24,41,24);
    } else if (kind == "sort") { p.drawLine(14,6,14,42); p.drawLine(6,14,14,6); p.drawLine(22,14,14,6); p.drawLine(34,6,34,42); p.drawLine(26,34,34,42); p.drawLine(42,34,34,42);
    } else if (kind == "bars") { p.setPen(Qt::NoPen); p.setBrush(color); for(int i=0;i<4;++i)p.drawRoundedRect(QRectF(4+i*11,31-i*8,7,14+i*8),3,3);
    } else if (kind == "trash") { p.drawRoundedRect(QRectF(13,14,23,29),2,2); p.drawLine(8,10,40,10); p.drawLine(18,4,30,4); p.drawLine(21,20,21,36); p.drawLine(28,20,28,36);
    } else if (kind == "edit") { QPolygonF poly; poly << QPointF(8,39)<<QPointF(12,28)<<QPointF(34,6)<<QPointF(42,14)<<QPointF(20,36)<<QPointF(8,39);p.drawPolygon(poly);p.drawLine(29,11,37,19);
    } else if (kind == "refresh") { p.drawArc(QRectF(6,6,36,36),35*16,270*16);p.drawLine(40,5,40,17);p.drawLine(29,17,40,17);
    } else if (kind == "exit") { p.drawLine(22,5,41,5);p.drawLine(41,5,41,43);p.drawLine(22,43,41,43);p.drawLine(5,24,30,24);p.drawLine(5,24,14,15);p.drawLine(5,24,14,33);
    } else if (kind == "lock") { p.drawRoundedRect(QRectF(13,4,22,28),11,11);p.setBrush(color);p.drawRoundedRect(QRectF(6,20,36,26),5,5);p.setPen(QPen(Qt::white,3));p.drawLine(24,29,24,38);
    } else if (kind == "shield") { p.setBrush(color);QPolygonF s;s<<QPointF(24,3)<<QPointF(43,10)<<QPointF(39,31)<<QPointF(24,46)<<QPointF(9,31)<<QPointF(5,10);p.drawPolygon(s);p.setPen(QPen(Qt::white,3));p.drawLine(15,24,22,31);p.drawLine(22,31,34,17);
    } else if (kind == "paw") { p.drawEllipse(QRectF(4,10,9,14));p.drawEllipse(QRectF(15,2,9,14));p.drawEllipse(QRectF(28,3,9,14));p.drawEllipse(QRectF(38,14,8,13));QPainterPath path;path.moveTo(11,36);path.cubicTo(10,27,21,19,26,22);path.cubicTo(33,23,40,32,36,39);path.cubicTo(32,48,26,37,21,40);path.cubicTo(16,44,11,41,11,36);p.drawPath(path);
    } else if (kind == "bulb") { p.drawEllipse(QRectF(13,3,22,28));p.drawLine(19,35,29,35);p.drawLine(21,41,27,41);p.drawLine(24,30,24,18);
    } else if (kind == "gear") { p.setBrush(color);for(int i=0;i<8;++i){p.save();p.translate(24,24);p.rotate(i*45);p.drawRect(QRectF(-4,-21,8,12));p.restore();}p.drawEllipse(QRectF(9,9,30,30));p.setBrush(QColor("#e9f6ff"));p.drawEllipse(QRectF(18,18,12,12));
    } else { QPolygonF doc;doc<<QPointF(11,4)<<QPointF(30,4)<<QPointF(39,14)<<QPointF(39,44)<<QPointF(11,44);p.drawPolygon(doc);p.drawLine(29,4,29,15);p.drawLine(29,15,39,15);p.drawLine(18,23,31,23);p.drawLine(18,31,30,31); }
    return QIcon(pix);
}
QLabel *symbol(const QString &name, int size=30, QColor color=QColor("#074778")) { auto *l=new QLabel; l->setPixmap(icon(name,color).pixmap(size,size)); l->setFixedSize(size,size);return l; }
QFrame *panel(const QString &title,const QString &glyph,QVBoxLayout *&body,bool green=false)
{
    auto *frame=new QFrame;frame->setObjectName(green?"greenPanel":"panel");auto *outer=new QVBoxLayout(frame);outer->setContentsMargins(0,0,0,0);outer->setSpacing(0);
    auto *head=new QWidget;head->setObjectName(green?"greenHeading":"heading");head->setFixedHeight(44);auto *row=new QHBoxLayout(head);row->setContentsMargins(16,5,12,0);row->setSpacing(14);row->addWidget(symbol(glyph,29,green?QColor("#008834"):QColor("#074778")));
    auto *titles=new QVBoxLayout;titles->setSpacing(4);titles->setContentsMargins(0,0,0,0);auto *label=new QLabel(title);label->setObjectName("sectionTitle");titles->addWidget(label);auto *underline=new QFrame;underline->setFixedSize(25,3);underline->setStyleSheet("background:#0c9631;border-radius:1px;");titles->addWidget(underline);row->addLayout(titles);row->addStretch();outer->addWidget(head);
    auto *content=new QWidget;body=new QVBoxLayout(content);body->setContentsMargins(12,9,12,9);outer->addWidget(content,1);return frame;
}
QLineEdit *edit(const QString &name) {auto *e=new QLineEdit;e->setObjectName(name);e->setMinimumHeight(35);return e;}
QComboBox *combo(const QString &name,const QString &value=QString()) { auto *c=new QComboBox;c->setObjectName(name);c->addItem(value);auto *arrow=new QLabel(QString::fromUtf8("⌄"),c);arrow->setStyleSheet("background:transparent;border:0;color:#315b7c;font-size:20px;");auto *arrowLayout=new QHBoxLayout(c);arrowLayout->setContentsMargins(0,0,9,4);arrowLayout->addStretch();arrowLayout->addWidget(arrow);arrow->setAttribute(Qt::WA_TransparentForMouseEvents);c->setMinimumHeight(35);return c;}
QLabel *fieldLabel(QString text) {auto *l=new QLabel(text+" <span style='color:#0087ff'>*</span>");l->setTextFormat(Qt::RichText);return l;}
}

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
    setWindowTitle("Smart Pet Care Center Management");setWindowIcon(icon("people"));resize(1280,920);setMinimumSize(1050,780);
    setStyleSheet(R"(
        QMainWindow {background:#f3fbff;}
        QWidget {font-family:'Segoe UI';font-size:15px;color:#062f60;}
        QFrame#panel {background:white;border:1px solid #b9e0fc;border-radius:8px;}
        QFrame#greenPanel {background:white;border:1px solid #b8e0c6;border-radius:8px;}
        QWidget#heading {background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #e1f3ff,stop:1 #ecf8ff);border-top-left-radius:8px;border-top-right-radius:8px;}
        QWidget#greenHeading {background:#edf9f2;border-top-left-radius:8px;border-top-right-radius:8px;}
        QLabel#sectionTitle {font-size:19px;font-weight:700;}
        QLineEdit,QComboBox {background:white;border:1px solid #b1c4da;border-radius:4px;padding:0 11px;selection-background-color:#137eae;}
        QLineEdit:focus,QComboBox:focus {border:1px solid #168cc4;}
        QComboBox::drop-down {border:0;width:28px;}
        QPushButton {background:qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 #edf8ff,stop:1 #e3f3ff);border:1px solid #b5dafa;border-radius:6px;font-weight:600;text-align:left;padding:5px 14px;}
        QPushButton:hover {background:#d5edff;}
        QPushButton#primary {background:qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 #167ca2,stop:1 #08618c);color:white;border-color:#087aaa;}
        QPushButton[green="true"] {background:#eefaf4;color:#008226;border-color:#bce5d2;}
        QStatusBar {background:#e5f4fe;border-top:1px solid #bddcf0;}
        QStatusBar QLabel {font-size:12px;color:#466180;}
    )");
    auto *central=new QWidget;setCentralWidget(central);auto *root=new QVBoxLayout(central);root->setContentsMargins(0,0,0,0);root->setSpacing(0);
    auto *banner=new QFrame;banner->setObjectName("banner");banner->setFixedHeight(92);banner->setStyleSheet("QFrame#banner{background:qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 #086696,stop:0.6 #134a75,stop:1 #075d7d);} QLabel{color:white;}");auto *bh=new QHBoxLayout(banner);bh->setContentsMargins(24,12,28,12);bh->setSpacing(20);bh->addWidget(symbol("people",62,Qt::white));auto *bt=new QVBoxLayout;bt->setSpacing(0);auto *title=new QLabel("Gestion des employés");title->setStyleSheet("font-size:34px;font-weight:700;");bt->addWidget(title);auto *sub=new QLabel("Smart Pet Care Center Management");sub->setStyleSheet("font-size:17px;color:#dfedf6;");bt->addWidget(sub);bh->addLayout(bt);bh->addStretch();auto *sep=new QFrame;sep->setFixedSize(1,52);sep->setStyleSheet("background:#d9efff;");bh->addWidget(sep);bh->addWidget(symbol("paw",55,Qt::white));auto *motto=new QLabel("Des animaux bien soignés,\ngrâce à une équipe exceptionnelle");motto->setStyleSheet("font-size:15px;");bh->addWidget(motto);root->addWidget(banner);
    auto *page=new QWidget;auto *layout=new QVBoxLayout(page);layout->setContentsMargins(20,12,20,5);layout->setSpacing(10);auto *scroll=new QScrollArea;scroll->setWidgetResizable(true);scroll->setFrameShape(QFrame::NoFrame);scroll->setWidget(page);root->addWidget(scroll,1);
    auto *top=new QHBoxLayout;top->setSpacing(12);QVBoxLayout *formBody;auto *form=panel("Informations de l'employé","person",formBody);form->setMinimumHeight(445);top->addWidget(form,67);
    auto *grid=new QGridLayout;grid->setContentsMargins(4,9,8,0);grid->setHorizontalSpacing(15);grid->setVerticalSpacing(19);
    QStringList left={"ID Employé","Nom","Prénom","Email","Téléphone"};QStringList ids={"lineedit_id","lineedit_nom","lineedit_prenom","lineedit_email","lineedit_telephone"};
    for(int i=0;i<5;++i){grid->addWidget(fieldLabel(left[i]),i,0);grid->addWidget(edit(ids[i]),i,1);}
    QStringList right={"Poste","Rôle","Mot de passe","Question de<br>sécurité","Réponse de<br>sécurité"};for(int i=0;i<5;++i)grid->addWidget(fieldLabel(right[i]),i,3);
    grid->addWidget(combo("combo_poste"),0,4);grid->addWidget(combo("combo_role"),1,4);auto *password=edit("lineedit_mot_de_passe");password->setEchoMode(QLineEdit::Password);password->addAction(icon("eye",QColor("#516d8c")),QLineEdit::TrailingPosition);grid->addWidget(password,2,4);grid->addWidget(combo("combo_question_securite"),3,4);grid->addWidget(edit("lineedit_reponse_securite"),4,4);grid->setColumnMinimumWidth(2,18);grid->setColumnStretch(1,1);grid->setColumnStretch(4,1);formBody->addLayout(grid);formBody->addStretch(1);
    auto *side=new QVBoxLayout;side->setSpacing(9);QVBoxLayout *actions;auto *actionPanel=panel("Actions de gestion","gear",actions);auto *buttons=new QGridLayout;buttons->setSpacing(8);
    QStringList texts={"Ajouter","Afficher","Modifier","Supprimer","Rechercher","Trier","Exporter PDF","Statistiques","Réinitialiser","Quitter"};QStringList icons={"plus","document","edit","trash","search","sort","pdf","bars","refresh","exit"};
    for(int i=0;i<10;++i){bool green=i==3||i==9;auto *b=new QPushButton(icon(icons[i],i==0?Qt::white:green?QColor("#008925"):QColor("#074778")),"  "+texts[i]);b->setObjectName(i==0?"primary":"button_"+icons[i]);b->setProperty("green",green);b->setIconSize(QSize(30,30));b->setMinimumHeight(43);buttons->addWidget(b,i/2,i%2);}actions->addLayout(buttons);actionPanel->setMinimumHeight(310);side->addWidget(actionPanel,1);
    QVBoxLayout *features;auto *featurePanel=panel("Fonctionnalités innovantes","bulb",features,true);auto *featureRow=new QHBoxLayout;featureRow->setSpacing(9);
    for(int i=0;i<2;++i){auto *b=new QPushButton;b->setProperty("green",true);b->setMinimumHeight(69);auto *bl=new QHBoxLayout(b);bl->setContentsMargins(9,5,7,5);bl->addWidget(symbol(i?"shield":"lock",34,QColor("#099c27")));auto *words=new QVBoxLayout;words->setSpacing(2);auto *t=new QLabel(i?"Gestion des\ndroits d'accès":"Réinitialiser\nmot de passe");t->setStyleSheet("font-weight:600;font-size:14px;");auto *s=new QLabel(i?"Permissions selon le rôle":"Par question de sécurité");s->setStyleSheet("font-size:10px;color:#466180;");words->addWidget(t);words->addWidget(s);bl->addLayout(words);auto *arrow=new QLabel("›");arrow->setStyleSheet("font-size:23px;color:#078535;");bl->addWidget(arrow);featureRow->addWidget(b);}features->addLayout(featureRow);featurePanel->setMinimumHeight(130);side->addWidget(featurePanel);top->addLayout(side,33);layout->addLayout(top,5);
    QVBoxLayout *filters;auto *filterPanel=panel("Recherche et filtres","search",filters);auto *filterRow=new QHBoxLayout;filterRow->setSpacing(18);filterRow->addWidget(new QLabel("Recherche"));auto *search=edit("lineedit_recherche");search->setPlaceholderText("Rechercher un employé par nom...");search->addAction(icon("search",QColor("#597796")),QLineEdit::LeadingPosition);filterRow->addWidget(search,4);filterRow->addWidget(new QLabel("Trier par"));filterRow->addWidget(combo("combo_tri","Nom"),2);filterRow->addWidget(new QLabel("Ordre"));filterRow->addWidget(combo("combo_ordre","Croissant"),2);filters->addLayout(filterRow);layout->addWidget(filterPanel);
    QVBoxLayout *listBody;auto *listPanel=panel("Liste des employés (0)","people",listBody);listBody->setContentsMargins(10,7,10,7);auto *tableFrame=new QFrame;tableFrame->setStyleSheet("QFrame#emptyTable{border:1px solid #c6dced;border-radius:5px;background:white;}");tableFrame->setObjectName("emptyTable");auto *tv=new QVBoxLayout(tableFrame);tv->setContentsMargins(0,0,0,4);tv->setSpacing(4);auto *header=new QWidget;auto *hr=new QHBoxLayout(header);hr->setContentsMargins(0,0,0,0);hr->setSpacing(0);QStringList cols={"ID","Nom","Prénom","Poste","Rôle","Email","Téléphone"};for(auto text:cols){auto *l=new QLabel(text);l->setAlignment(Qt::AlignCenter);l->setFixedHeight(36);l->setStyleSheet("background:#e6f4ff;border-right:1px solid #bedbf0;border-bottom:1px solid #bedbf0;font-weight:600;font-size:14px;");hr->addWidget(l,1);}tv->addWidget(header);tv->addStretch();auto *emptyIcon=symbol("people",32,QColor("#a2b4c8"));tv->addWidget(emptyIcon,0,Qt::AlignHCenter);auto *empty=new QLabel("<b>Aucun employé trouvé.</b><br><span style='color:#7991ae'>Utilisez les actions ci-dessus pour ajouter un employé<br>ou effectuez une recherche.</span>");empty->setAlignment(Qt::AlignCenter);empty->setStyleSheet("color:#59738f;font-size:12px;");tv->addWidget(empty);tv->addStretch();listBody->addWidget(tableFrame);listPanel->setMinimumHeight(200);layout->addWidget(listPanel,2);
    statusBar()->setSizeGripEnabled(false);statusBar()->setFixedHeight(34);statusBar()->addWidget(symbol("people",20,QColor("#466180")));statusBar()->addWidget(new QLabel("  0 employé(s)"));statusBar()->addPermanentWidget(symbol("paw",20));statusBar()->addPermanentWidget(new QLabel("  Smart Pet Care Center Management    "));
    const QRect available=QGuiApplication::primaryScreen()->availableGeometry();resize(qMin(1280,available.width()-30),qMin(920,available.height()-50));
}
