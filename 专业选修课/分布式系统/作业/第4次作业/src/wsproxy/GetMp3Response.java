
package wsproxy;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>anonymous complex type的 Java 类。
 * 
 * <p>以下模式片段指定包含在此类中的预期内容。
 * 
 * <pre>
 * &lt;complexType>
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="GetMp3Result" type="{http://www.w3.org/2001/XMLSchema}base64Binary" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "", propOrder = {
    "getMp3Result"
})
@XmlRootElement(name = "GetMp3Response")
public class GetMp3Response {

    @XmlElement(name = "GetMp3Result")
    protected byte[] getMp3Result;

    /**
     * 获取getMp3Result属性的值。
     * 
     * @return
     *     possible object is
     *     byte[]
     */
    public byte[] getGetMp3Result() {
        return getMp3Result;
    }

    /**
     * 设置getMp3Result属性的值。
     * 
     * @param value
     *     allowed object is
     *     byte[]
     */
    public void setGetMp3Result(byte[] value) {
        this.getMp3Result = value;
    }

}
