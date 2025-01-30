import React, { useEffect, useState, useRef, useCallback } from "react";

const WebSocketManager = () => {
  const [messages, setMessages] = useState({});
  const connections = useRef({});

  const handleNewMessage = useCallback((id, data) => {
    setMessages((prevMessages) => ({
      ...prevMessages,
      [id]: data,
    }));
  }, []);

  useEffect(() => {
    for (let i = 0; i <= 99; i++) {
      const startTime = performance.now();

      const endpoint = `ws://localhost:${i < 10 ? "800" + i : "80" + i}/endpoint${i + 1}`;
      const ws = new WebSocket(endpoint);

      ws.onopen = () => {
        const endTime = performance.now();        
        console.log(`WebSocket ${i} connected`);
        console.log(`Start: ${startTime}`)
        console.log(`End: ${endTime}`)
        console.log("======================")        
      }
      ws.onmessage = (event) => {
        console.log(`Message from WebSocket ${i}:`, event.data);
        handleNewMessage(i, event.data);
      };
      ws.onerror = (error) => console.error(`WebSocket ${i} error:`, error);
      ws.onclose = () => console.log(`WebSocket ${i} closed`);

      connections.current[i] = ws;
    }

    return () => {
      Object.values(connections.current).forEach((ws) => ws.close());
    };
  }, [handleNewMessage]);

  return (
    <div style={{ padding: "20px" }}>
      <h1>Data 1-1-ws (8xxx) WebSocket</h1>

      <div
        style={{
          display: "grid",
          gridTemplateColumns: "repeat(auto-fit, minmax(300px, 1fr))",
          gap: "20px",
        }}
      >
        {Array.from({ length: 100 }, (_, i) => i).map((id) => (
          <div
            key={id}
            style={{
              border: "1px solid #ddd",
              borderRadius: "5px",
              padding: "10px",
            }}
          >
            <h3 style={{ margin: "0 0 10px" }}>WebSocket {id + 1}</h3>
            <ul
              style={{
                maxHeight: "200px",
                overflowY: "auto",
                listStyle: "none",
                padding: 0,
                margin: 0,
              }}
            >
              <li
                style={{
                  background: "#f9f9f9",
                  margin: "5px 0",
                  padding: "5px",
                  borderRadius: "3px",
                }}
              >
                {messages[id] || "NULL"}
              </li>
            </ul>
          </div>
        ))}
      </div>
    </div>
  );
};

export default WebSocketManager;
