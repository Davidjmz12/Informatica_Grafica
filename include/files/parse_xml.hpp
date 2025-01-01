#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

class XmlNode {
public:
    std::string tag;
    std::unordered_map<std::string, std::string> attributes;
    std::string content;
    std::vector<XmlNode> children;

    friend std::ostream& operator<<(std::ostream& os, const XmlNode& node) {
        printXmlNode(os, node, 0);
        return os;
    }

    bool hasAttribute(const std::string& key) const {
        return attributes.find(key) != attributes.end();
    }

    bool hasChild(const std::string& tag) const {
        for (const auto& child : children) {
            if (child.tag == tag) {
                return true;
            }
        }
        return false;
    }

    XmlNode getChild(const std::string& tag) const {
        for (const auto& child : children) {
            if (child.tag == tag) {
                return child;
            }
        }
        throw std::runtime_error("Child with tag: " + tag + " not found.");
    }

    std::vector<XmlNode> getChildren(const std::string& tag) const {
        std::vector<XmlNode> result;
        for (const auto& child : children) {
            if (child.tag == tag) {
                result.push_back(child);
            }
        }
        return result;
    }

    std::string getAttribute(const std::string& key) const {
        auto it = attributes.find(key);
        if (it == attributes.end()) {
            throw std::runtime_error("Attribute with key: " + key + " not found.");
        }
        return it->second;
    }

    std::string getContentChild(const std::string& tag) const {
        return getChild(tag).content;
    }

private:
    static void printXmlNode(std::ostream& os, const XmlNode& node, int indent) {
        std::string indentation(indent, ' ');
        os << indentation << "Tag: " << node.tag << "\n";

        if (!node.attributes.empty()) {
            os << indentation << "  Attributes:\n";
            for (const auto& [key, value] : node.attributes) {
                os << indentation << "    " << key << " = " << value << "\n";
            }
        }

        if (!node.content.empty()) {
            os << indentation << "  Content: " << node.content << "\n";
        }

        if (!node.children.empty()) {
            os << indentation << "  Children:\n";
            for (const auto& child : node.children) {
                printXmlNode(os, child, indent + 4);
            }
        }
    }
};

class XmlReader {
public:
    XmlNode parse(const std::string& file_str) {
        std::ifstream file(file_str);
        if (!file.is_open())
            throw std::runtime_error("Failed to open file.");

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string xml = buffer.str();

        std::string trimmedXml = std::regex_replace(xml, std::regex("\n|\t"), "");
        return parseNode(trimmedXml);
    }

private:
    XmlNode parseNode(const std::string& xml) {
        XmlNode node;

        std::regex tagRegex("<([a-zA-Z0-9_]+)([^>]*)>");
        std::smatch tagMatch;

        if (std::regex_search(xml, tagMatch, tagRegex)) {
            node.tag = tagMatch[1];

            std::string attributesStr = tagMatch[2];
            node.attributes = parseAttributes(attributesStr);

            size_t contentStart = tagMatch.position() + tagMatch.length();
            size_t contentEnd = xml.find("</" + node.tag + ">");

            if (contentEnd != std::string::npos) {
                std::string innerContent = xml.substr(contentStart, contentEnd - contentStart);
                node.children = parseChildren(innerContent);
                if (node.children.empty()) {
                    node.content = innerContent;
                }
            }
        }

        return node;
    }

    std::unordered_map<std::string, std::string> parseAttributes(const std::string& attributesStr) {
        std::unordered_map<std::string, std::string> attributes;
        std::regex attrRegex("([a-zA-Z0-9_]+)=\"([^\"]*)\"");
        auto attrsBegin = std::sregex_iterator(attributesStr.begin(), attributesStr.end(), attrRegex);
        auto attrsEnd = std::sregex_iterator();

        for (auto it = attrsBegin; it != attrsEnd; ++it) {
            attributes[(*it)[1]] = (*it)[2];
        }

        return attributes;
    }

    std::vector<XmlNode> parseChildren(const std::string& content) {
        std::vector<XmlNode> children;
        std::regex childRegex("<([a-zA-Z0-9_]+)([^>]*)>.*?</\\1>");
        auto childrenBegin = std::sregex_iterator(content.begin(), content.end(), childRegex);
        auto childrenEnd = std::sregex_iterator();

        for (auto it = childrenBegin; it != childrenEnd; ++it) {
            children.push_back(parseNode(it->str()));
        }

        return children;
    }
};