### 说明
当前仅支持解析整数数值字面量，规则如下：

***program ::= NumericLiteral;***

#### 测试类 `NumericLiteral`
`NumericLiteral` 是一个测试类，主要用于验证解析器在当前简单文法下对数值字面量的解析能力是否正确。

本测试类包含一个测试方法 `Integer`，专门测试解析整数类型的字面量。
- **输入**：
  ```javascript
  123
  ```
- **输出**：
  ```json
  {
      "type": "NumericLiteral",
      "value": 123
  }
  ```
