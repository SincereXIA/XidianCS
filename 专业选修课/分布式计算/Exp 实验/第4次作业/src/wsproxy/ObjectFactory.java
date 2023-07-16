
package wsproxy;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlElementDecl;
import javax.xml.bind.annotation.XmlRegistry;
import javax.xml.namespace.QName;


/**
 * This object contains factory methods for each 
 * Java content interface and Java element interface 
 * generated in the wsproxy package. 
 * <p>An ObjectFactory allows you to programatically 
 * construct new instances of the Java representation 
 * for XML content. The Java representation of XML 
 * content can consist of schema derived interfaces 
 * and classes representing the binding of schema 
 * type definitions, element declarations and model 
 * groups.  Factory methods for each of these are 
 * provided in this class.
 * 
 */
@XmlRegistry
public class ObjectFactory {

    private final static QName _DataSet_QNAME = new QName("http://WebXml.com.cn/", "DataSet");
    private final static QName _Base64Binary_QNAME = new QName("http://WebXml.com.cn/", "base64Binary");
    private final static QName _ArrayOfString_QNAME = new QName("http://WebXml.com.cn/", "ArrayOfString");

    /**
     * Create a new ObjectFactory that can be used to create new instances of schema derived classes for package: wsproxy
     * 
     */
    public ObjectFactory() {
    }

    /**
     * Create an instance of {@link TranslatorResponse }
     * 
     */
    public TranslatorResponse createTranslatorResponse() {
        return new TranslatorResponse();
    }

    /**
     * Create an instance of {@link TranslatorString }
     * 
     */
    public TranslatorString createTranslatorString() {
        return new TranslatorString();
    }

    /**
     * Create an instance of {@link SuggestWordResponse }
     * 
     */
    public SuggestWordResponse createSuggestWordResponse() {
        return new SuggestWordResponse();
    }

    /**
     * Create an instance of {@link ArrayOfString }
     * 
     */
    public ArrayOfString createArrayOfString() {
        return new ArrayOfString();
    }

    /**
     * Create an instance of {@link DataSet }
     * 
     */
    public DataSet createDataSet() {
        return new DataSet();
    }

    /**
     * Create an instance of {@link TranslatorSentenceStringResponse }
     * 
     */
    public TranslatorSentenceStringResponse createTranslatorSentenceStringResponse() {
        return new TranslatorSentenceStringResponse();
    }

    /**
     * Create an instance of {@link GetMp3Response }
     * 
     */
    public GetMp3Response createGetMp3Response() {
        return new GetMp3Response();
    }

    /**
     * Create an instance of {@link TranslatorReferString }
     * 
     */
    public TranslatorReferString createTranslatorReferString() {
        return new TranslatorReferString();
    }

    /**
     * Create an instance of {@link TranslatorReferStringResponse }
     * 
     */
    public TranslatorReferStringResponse createTranslatorReferStringResponse() {
        return new TranslatorReferStringResponse();
    }

    /**
     * Create an instance of {@link TranslatorResponse.TranslatorResult }
     * 
     */
    public TranslatorResponse.TranslatorResult createTranslatorResponseTranslatorResult() {
        return new TranslatorResponse.TranslatorResult();
    }

    /**
     * Create an instance of {@link TranslatorSentenceString }
     * 
     */
    public TranslatorSentenceString createTranslatorSentenceString() {
        return new TranslatorSentenceString();
    }

    /**
     * Create an instance of {@link TranslatorStringResponse }
     * 
     */
    public TranslatorStringResponse createTranslatorStringResponse() {
        return new TranslatorStringResponse();
    }

    /**
     * Create an instance of {@link Translator }
     * 
     */
    public Translator createTranslator() {
        return new Translator();
    }

    /**
     * Create an instance of {@link GetMp3 }
     * 
     */
    public GetMp3 createGetMp3() {
        return new GetMp3();
    }

    /**
     * Create an instance of {@link SuggestWord }
     * 
     */
    public SuggestWord createSuggestWord() {
        return new SuggestWord();
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link DataSet }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://WebXml.com.cn/", name = "DataSet")
    public JAXBElement<DataSet> createDataSet(DataSet value) {
        return new JAXBElement<DataSet>(_DataSet_QNAME, DataSet.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link byte[]}{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://WebXml.com.cn/", name = "base64Binary")
    public JAXBElement<byte[]> createBase64Binary(byte[] value) {
        return new JAXBElement<byte[]>(_Base64Binary_QNAME, byte[].class, null, ((byte[]) value));
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfString }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://WebXml.com.cn/", name = "ArrayOfString")
    public JAXBElement<ArrayOfString> createArrayOfString(ArrayOfString value) {
        return new JAXBElement<ArrayOfString>(_ArrayOfString_QNAME, ArrayOfString.class, null, value);
    }

}
