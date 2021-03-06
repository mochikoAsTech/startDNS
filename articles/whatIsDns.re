= DNSの仕組み

ドメイン名を買ってウェブサーバにコンテンツを載せたらそれだけでサイトが見られるでしょうか？

いいえ、ドメイン名とウェブサーバがそれぞれ存在しているだけではサイトは見られません。ドメイン名とウェブサーバを紐づける必要があります。でもサーバはともかくとしてドメイン名は手で触れるようなものではないので、この2つをリアルに紐で結ぶことはできません。ドメイン名とサーバを紐づけるには一体どうしたらいいのでしょう？

そこで出てくるのがDNSです。この章ではDNSの仕組みをしっかり学んでいきましょう。

//pagebreak

== DNSとは

DNSサーバのDNSはDomain Name Systemの略で、日本語に直訳すると「ドメイン名の管理システム」といったところです。一口にDNSサーバと言っても、その実態は「ネームサーバ」と「フルリゾルバ」の2つに分かれています。異なる働きをする2つのサーバがどちらも「DNSサーバ」と呼ばれていることが、DNSを分かりにくくしている一因だと筆者は思います。DNSの仕組みの解説に入る前にきちんとこの2つを整理しておきましょう。

=== ネームサーバ

ネームサーバは「電話帳」のような役割を果たします。

電話帳には名前とそれに紐づく電話番号が書いてありますが、ネームサーバにはドメイン名とそれに紐づくIPアドレスが登録されています。

ネームサーバは「DNSコンテンツサーバ」「権威DNSサーバ」@<fn>{authoritative}と呼ばれることもありますが、本著では統一してネームサーバと呼びます。

//footnote[authoritative][権威DNSサーバという日本語は「Authoritative Server」（権威のあるサーバ）から来ているようです。DNSで用いられる用語の定義はRFC8499を参照。@<href>{https://tools.ietf.org/html/rfc8499}]

=== フルリゾルバ

フルリゾルバは「秘書」のような役割を果たします。

フルリゾルバに「このドメイン名に紐づくIPアドレスが知りたいの。調べてきて」と言うと、あちこちのネームサーバに聞きまわってIPアドレスを調べてきて教えてくれます。しかも一度調べると一定期間はそのドメイン名とIPアドレスの紐づけを記憶（キャッシュ）するため、もう1回同じことを聞くと今度はすぐに教えてくれます。

フルリゾルバは「DNSキャッシュサーバ」「フルサービスリゾルバ」と呼ばれることもありますが、本著では統一してフルリゾルバと呼びます。

あなたがブラウザでウェブサイトを見るときは必ずこのフルリゾルバにドメイン名の名前解決を頼んでいます。「でもそんなもの使う設定をした記憶ないけど…」と思われるかも知れませんが、会社のオフィスなら情シスが、家庭なら契約しているISP@<fn>{isp}がフルリゾルバを用意していて、自動で「このフルリゾルバを使ってね」と割り当てられているので意識していないだけです。

//footnote[isp][インターネットサービスプロバイダの略。インターネットへの接続サービスを提供する電気通信事業者のこと]

情シスやISPがそれぞれのネットワーク内で提供しているフルリゾルバの他に、Google Public DNS@<fn>{googlePublicDns}の8.8.8.8やCloudflareの1.1.1.1@<fn>{cloudflare}のようにだれでも無料で使えるオープンリゾルバというものがあります。2013年8月にOCN@<fn>{ocn}のフルリゾルバが死んでOCNユーザがインターネットに接続できなくなる@<fn>{incident}障害が発生しました。そのとき「DNSサーバの設定を8.8.8.8にすれば直るよ」という情報がTwitterで出回りました（@<img>{twitter8888}）。

//footnote[googlePublicDns][@<href>{https://developers.google.com/speed/public-dns/}]
//footnote[cloudflare][@<href>{https://1.1.1.1/ja-jp/}]
//footnote[ocn][NTTコミュニケーションズが運営する日本最大級のインターネットサービスプロバイダ]
//footnote[incident][ドメイン名からIPアドレスを引く名前解決ができないことでウェブサーバのIPが分からず、サイトが見られなくなったりゲームやアプリなどのサービスが使えなくなったりした、ということです]

//image[twitter8888][DNSサーバを8.8.8.8にするとつながるというツイート][scale=0.8]{
//}

これは使用するフルリゾルバを故障中のOCNのものからGoogle Public DNSに変更したことで名前解決が出来るようになってサイトも見られるようになった、ということです。

フルリゾルバはもちろんサーバでも使っています。Linuxサーバなら@<code>{/etc/resolv.conf}というファイルを見てみましょう。@<code>{resolv.conf}の@<code>{nameserver}という項目で指定されているのがそのサーバのフルリゾルバです。

//cmd{
$ cat /etc/resolv.conf
options timeout:2 attempts:5
nameserver 172.31.0.2
//}

== お名前.comのページが表示されるまで

@<chapref>{domain}の最後で、自分が買ったドメイン名をブラウザで開いてみたところ、お名前.comの「このドメインは、お名前.comで取得されています。」（@<img>{onamaeCm}）というページが表示されました。

//image[onamaeCm][http://自分のドメイン名/を開くとお名前.comの広告が出る][scale=0.8]{
//}

ブラウザでhttp://自分のドメイン名/を開いたときに、このページが表示されるまでの流れは次（@<img>{afterBuyingDomain}）のようになっていました。

//image[afterBuyingDomain][ページが表示されるまでのフルリゾルバとネームサーバの仕組み][scale=0.8]{
//}

ブラウザのアドレスバーに自分のドメイン名を入れてEnterを押してからページが表示されるまでの一瞬の間に、なんとこれだけの名前解決が行われていたのです。

== ゾーンと委任

このようにDNSは「1台が何もかも知っている」という集中管理ではなく、「いくつかのネームサーバに聞けば答えにたどり着く」という管理権限の分散された仕組みになっています。先ほどの名前解決を会社に例えると次のようになります。

//image[secretaryLikeNameServer][Bさんに電話をかけるまでの流れ][scale=0.8]{
//}

秘書がフルリゾルバで、社長やA部長やマネージャのCさんがネームサーバ、Bさんがウェブサーバに当てはまります。

社長がA部門のことはA部長に任せていたように、ルートネームサーバはfunのことは@<code>{a.nic.fun}に任せていました。このとき「A部門」や「@<code>{fun}」、「Bさん」や「@<code>{startdns.fun}」のような範囲をゾーンと呼びます。

A部長は自分が任されているA部門の中で、BさんについてはCマネージャに管理を任せていました。同様に@<code>{a.nic.fun}というネームサーバは、自分が任されているfunというゾーンの中で、funのサブドメインにあたる@<code>{startdns.fun}というゾーンについては@<code>{dns1.onamae.com}に任せていました。

このように自身が任されているゾーンを分割して、その一部のゾーンを他のネームサーバに任せることを委任と呼びます。

つまり社長がA部門というゾーンをA部長に委任していたように、ルートネームサーバはfunというゾーンを@<code>{a.nic.fun}に委任していた、ということです。ゾーンを委任されているネームサーバは、そのドメインについて権威を持つので、サブドメインを作ったり、任されたゾーンをさらに分割して他のネームサーバに委任したりできます。

== リソースレコード

ネームサーバのお腹の中にある電話帳は管理しやすいように「@<code>{startdns.fun}の電話帳」「@<code>{example.com}の電話帳」のようにドメインごとに分かれています。この一冊一冊の電話帳が管理している範囲を前述のとおりゾーンと呼びます。

そしてこのゾーンの中にある「ドメイン名とIPアドレスの紐づけ」ひとつひとつのことをリソースレコードと呼びます。たとえば@<code>{startdns.fun}のゾーンの中には「@<code>{startdns.fun}とそれに紐づくIPアドレス」や「@<code>{www.startdns.fun}とそれに紐づくIPアドレス」、「@<code>{staging.startdns.fun}とそれに紐づくIPアドレス」のようにたくさんのリソースレコードを書くことができます。

先ほどの会社の例で言うと、A部長はA部門というゾーンを管理していて、マネージャのCさんはBさんというゾーンを管理してます。そしてCさんが管理するBさんというゾーンの中には「Bさんの携帯番号は090-〇〇〇〇-〇〇〇〇」や「Bさんの自宅番号は03-〇〇〇〇-〇〇〇〇」といったリソースレコードがあるのです。

リソースレコードには次（@<table>{resourceRecord}）のようにAレコードやMXレコードといった種類があり、それぞれ書き方も決められています。

//table[resourceRecord][リソースレコードの種類]{
リソースレコードのタイプ	値の意味
------------------------------------
Aレコード	ドメイン名に紐づくIPアドレス（例：ウェブサーバ）
NSレコード	ドメイン名のゾーンを管理するネームサーバ
MXレコード	ドメイン名に紐づくメール受信サーバ
TXT（SPF）	このドメイン名のメール送信元サーバ
SOA	ドメイン名のゾーンの管理情報
CNAME	このドメイン名の別名でリソースレコードの参照先
//}

それぞれのリソースレコードをどういうときに使うのか？については@<chapref>{aws}や@<chapref>{dig}で具体例を見て、手を動かしながら確認していきましょう。

== hostsファイル

ところでDNSという管理権限が分散された仕組みが生まれる以前は、hostsファイル@<fn>{hosts}と呼ばれるテキストファイルに「名前とIPアドレスの対応」がすべて詰め込まれて一元管理されていました。hostsファイルは現在も使われており、実は名前解決は「先ずはhostsファイルで探す→hostsファイルになければフルリゾルバに問い合わせ」という順番で行われることが多い@<fn>{nsswitch}です。

//footnote[hosts][ホスツファイルと読みます。ホスト名（サーバの名前）とIPアドレスの対応がたくさん記述されているのでhostの複数形でhostsです]
//footnote[nsswitch][Linuxサーバの場合、名前解決の順番は@<code>{/etc/nsswitch.conf}のhost行で@<code>{hosts: files dns}のように指定されています。filesはhostsファイルのこと、dnsはDNSに問い合わせることを表しています]

それでは実際にhostsファイルの利用を試してみましょう。

=== Windowsでhostsを使ってみよう

「メモ帳」で検索したらアイコンを右クリックして「管理者として実行」をクリック（@<img>{startDNS5}）します。

//image[startDNS5][メモ帳を管理者として実行][scale=0.6]{
//}

メモ帳が起動したら「ファイル＞開く」で@<code>{C:\Windows\System32\drivers\etc}というフォルダの中にある@<code>{hosts}というファイルを開いてください。（@<img>{startDNS6}）フォルダ内にファイルが見当たらない場合は、右下の「テキスト文書 (*.txt)」を「すべてのファイル (*.*)」にします。

//image[startDNS6][メモ帳でhostsファイルを開く][scale=0.8]{
//}

メモ帳でhostsファイルを開いたら、いちばん下に次の1行を書き足してみましょう。

//cmd{
150.95.255.38 we.love.caaaaaaaaaaaaaat
//}

猫への愛が爆発していますが、もちろんこんなドメイン名は実在しません。ctrl+sでhostsファイルの変更を保存したら、ブラウザで@<href>{http://we.love.caaaaaaaaaaaaaat/}を開いてみましょう。（@<img>{startDNS7}）「このドメインは、お名前.comで取得されています。」というページが表示されました。

//image[startDNS7][存在しないドメイン名でページが表示された][scale=0.8]{
//}

これは@<code>{we.love.caaaaaaaaaaaaaat}という架空のドメイン名と、お名前.comのウェブサーバ（@<code>{150.95.255.38}）のIPアドレスをhostsファイルで紐付けたことで、ページが表示されるようになったという仕組みです。@<fn>{excuse}もちろんこのURLを叩いても、hostsファイルに@<code>{150.95.255.38 we.love.caaaaaaaaaaaaaat}を書き足したパソコンでしかページは表示されません。

//footnote[excuse][@<code>{$ dig we.love.caaaaaaaaaaaaaat @dns1.onamae.com +short +norec}で@<code>{150.95.255.38}を返してくれるネームサーバすごいなという気持ちです。お名前.comさん、勝手に実験台にしてすみません]

このようにhostsファイルに書き込むことで、その環境でだけドメイン名に紐付くIPアドレスを変えられるので、サイトリニューアルでウェブサーバを引っ越すような場合に「hostsファイルにこれを書くとブラウザで新しいサイトが確認できる」のような使い方ができます。

=== MacやLinuxでhostsを使ってみよう

MacやLinuxで同じことを試したかったら、@<code>{/etc/hosts}というファイルのいちばん下に次の1行を書き足してみましょう。

//cmd{
150.95.255.38 we.love.caaaaaaaaaaaaaat
//}

その上で、ブラウザで@<href>{http://we.love.caaaaaaaaaaaaaat/}を開くか、ターミナルで次のcurlコマンドを叩くと動作確認ができます。@<fn>{defaultHost}

//cmd{
$ curl http://we.love.caaaaaaaaaaaaaat/

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
 "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ja" lang="ja">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="Content-Style-Type" content="text/css" />
<meta http-equiv="Content-Script-Type" content="text/javascript" />
<title>we.love.caaaaaaaaaaaaaat – このドメインはお名前.comで取得されています。</title>
<link href="http://error.gmo.jp/contents/setstyle.css"
 rel="stylesheet" type="text/css" />
</head>
（後略）
//}

//footnote[defaultHost][これはお名前.comのウェブサーバ（@<code>{150.95.255.38}）がどんなホスト名でリクエストが来てもレスポンスを返すようになっていたため、勝手な名前でリクエストしてもページが表示されています。hostsファイルを設定しただけでは、ウェブサーバ側の設定次第でページが返ってこない可能性も十分あります]