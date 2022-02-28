import React from 'react';
import Stack from 'react-bootstrap/Stack'
import {Button, Col, Container, Row} from "react-bootstrap";

class Main extends React.Component {
    render() {
        return (
            <Container>
                <Row>
                    <Col>
                        <Stack gap={3} className="col-md-5 mx-auto">
                            <Button variant="secondary" href='/players'>Players</Button>
                            <Button variant="secondary" href='/games'>Games</Button>
                            <Button variant="secondary" href='/ranks'>Ranks</Button>
                        </Stack>
                    </Col>
                </Row>
            </Container>
        );
    }
}

export default Main;